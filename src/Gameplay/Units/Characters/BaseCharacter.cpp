#include <chrono>
#include <iostream>

#include "Assets.h"
#include "Gameplay/Units/Characters/BaseCharacter.h"
#include "Utilities/AStar.h"

using namespace std::chrono_literals;

ActionProperties::ActionProperties(sf::Time animationTimeout, uint8_t frames)
    : animationTimeout(animationTimeout), frames(frames)
{
}

BaseCharacter::BaseCharacter(sf::Vector2u position, unsigned int hp, unsigned int maxHP,
                             const sf::Texture &texture, sf::IntRect area)
    : BaseUnit(position, hp, maxHP, texture, area)
{
}

void BaseCharacter::moveTo(sf::Vector2u targetPosition, std::function<bool(sf::Vector2u)> isTileFree,
                           bool attackThreadClosureRequired, bool stopAtNeighborTile)
{
    // если приходит запрос на новое действие - завершаем действующие потоки
    if (attackThreadClosureRequired)
        stopAttackThread();
    stopMovementThread(); // предыдущий поток перемещения в любом случае должен быть закрыт

    // инициализируем новый поток перемещения к указанной позиции
    movementThread = std::jthread([this, targetPosition, isTileFree, stopAtNeighborTile](std::stop_token stopToken) {
        while (not stopToken.stop_requested())
        {
            auto timer = std::chrono::steady_clock::now();

            while (std::chrono::steady_clock::now() - timer < std::chrono::milliseconds{1000 / (int)speed})
                if (stopToken.stop_requested()) // если за отсечку поступила отмена команды - прерываем цикл
                    break;

            std::deque<sf::Vector2u> recalculatedPath;

            if (stopAtNeighborTile)
            {
                auto neighbors = getNeighbors(targetPosition, isTileFree);

                if (std::find(neighbors.cbegin(), neighbors.cend(), targetPosition) != neighbors.cend())
                    break;

                for (auto &neighbor : neighbors)
                {
                    if (stopToken.stop_requested()) // если за отсечку поступила отмена команды - прерываем цикл
                        break;

                    // рассчитываем новый маршрут
                    auto recalculatedNeighborPath = calculatePath(position, neighbor, isTileFree, &stopToken);

                    if (recalculatedPath.empty() or (not recalculatedNeighborPath.empty() and
                                                     recalculatedPath.size() > recalculatedNeighborPath.size()))
                        recalculatedPath = recalculatedNeighborPath;
                }
            }
            else // рассчитываем новый маршрут
                recalculatedPath = calculatePath(position, targetPosition, isTileFree, &stopToken);

            // если маршрут пуст или новый оказался короче текущего - обновляем маршрут
            if (not recalculatedPath.empty())
                if (path.empty() or path.size() > recalculatedPath.size())
                    setPath(recalculatedPath);

            if (stopToken.stop_requested()) // если за отсечку поступила отмена команды - прерываем цикл
                break;

            if (not path.empty())
            {
                auto nextPosition = path.front(); // получаем следующее положение игрока
                path.pop_front(); // удаляем следующую позицию из маршрута

                direction = getDirection(position, nextPosition); // меняем его взгляд в направлении движения
                action = Action::Walk;
                position = nextPosition;
            }
            else
                break;
        }

        path.clear();          // очищаем маршрут
        action = Action::Idle; // переводим анимацию персонажа в режим бездействия
    });
}

void BaseCharacter::attack(std::unique_ptr<BaseUnit> &targetUnit, std::function<bool(sf::Vector2u)> isTileFree)
{
    // если приходит запрос на атаку новой цели - завершаем все потоки персонажа
    stopMovementThread();
    stopAttackThread();

    // инициализируем новый поток перемещения к указанной позиции
    attackThread = std::jthread([this, &targetUnit, isTileFree](std::stop_token stopToken) {
        while (not stopToken.stop_requested() and targetUnit != nullptr and targetUnit->getHP() > 0)
        {
            if (BaseUnit::distance(position, targetUnit->getPosition()) == 1) // цель в поле досягаемости
            {
                stopMovementThread();
                action = Action::Attack;

                auto attackPrepareTimer = std::chrono::steady_clock::now();

                while (std::chrono::steady_clock::now() - attackPrepareTimer <
                       std::chrono::milliseconds{animationProperties[Action::Attack].animationTimeout.asMilliseconds()})
                    if (stopToken.stop_requested()) // если за отсечку поступила отмена команды - прерываем цикл
                        break;

                direction = getDirection(position, targetUnit->getPosition());
                animationFrame = 1; //  устанавливаем кадр удара

                auto attackTimer = std::chrono::steady_clock::now();

                while (std::chrono::steady_clock::now() - attackTimer <
                       std::chrono::milliseconds{animationProperties[Action::Attack].animationTimeout.asMilliseconds()})
                    if (stopToken.stop_requested()) // если за отсечку поступила отмена команды - прерываем цикл
                        break;

                auto enemyHP = targetUnit->getHP();
                targetUnit->setHP(enemyHP - damage);

                if ((int)enemyHP - damage > 0)
                {
                    auto attackRestTimer = std::chrono::steady_clock::now();

                    while (std::chrono::steady_clock::now() - attackRestTimer <
                           std::chrono::milliseconds{
                               animationProperties[Action::Attack].animationTimeout.asMilliseconds() *
                               (animationProperties[Action::Attack].frames - 2)})
                        if (stopToken.stop_requested()) // если за отсечку поступила отмена команды - прерываем цикл
                            break;
                }
                else
                {
                    while (targetUnit != nullptr)
                        std::this_thread::yield();

                    while (movementThread.joinable() and not stopToken.stop_requested())
                        std::this_thread::yield();
                }
            }
            else
            {
                moveTo(targetUnit->getPosition(), isTileFree, false, true);

                while (movementThread.joinable() and BaseUnit::distance(position, targetUnit->getPosition()) > 1 and
                       not stopToken.stop_requested())
                    std::this_thread::yield();
            }
        }

        stopMovementThread();
        action = Action::Idle;
    });
}

float BaseCharacter::getSpeed() const
{
    return speed;
}

std::deque<sf::Vector2u> BaseCharacter::getPath() const
{
    return path;
}

void BaseCharacter::setSpeed(float speed)
{
    this->speed = speed;
}

void BaseCharacter::setPath(const std::deque<sf::Vector2u> &path)
{
    this->path = path;
}

void BaseCharacter::stopMovementThread()
{
    if (movementThread.joinable())
    {
        movementThread.request_stop();
        movementThread.join();
    }
}

void BaseCharacter::stopAttackThread()
{
    if (attackThread.joinable())
    {
        attackThread.request_stop();
        attackThread.join();
    }
}

void BaseCharacter::updateArea()
{
    switch (action)
    {
    case Action::Idle:
        area.top = 0;
        area.left = animationFrame * SPRITE_SIZE_PX;
        break;
    case Action::Walk:
        area.top = 0;
        area.left = (animationFrame + 1) * SPRITE_SIZE_PX;
        break;
    case Action::Attack:
        area.top = 8 * SPRITE_SIZE_PX;
        area.left = animationFrame * SPRITE_SIZE_PX;
    }

    switch (direction)
    {
    case Direction::Down:
        break;
    case Direction::Up:
        area.top += 1 * SPRITE_SIZE_PX;
        break;
    case Direction::Right:
        area.top += 2 * SPRITE_SIZE_PX;
        break;
    case Direction::Left:
        area.top += 3 * SPRITE_SIZE_PX;
        break;
    }
}

void BaseCharacter::update()
{
    if (animationClock.getElapsedTime() >= animationProperties[action].animationTimeout)
    {
        animationClock.restart();
        animationFrame = (animationFrame + 1) % animationProperties[action].frames;

        updateArea();
    }
}

BaseCharacter::Direction BaseCharacter::getDirection(sf::Vector2u fromPoint, sf::Vector2u toPoint)
{
    if (fromPoint.x < toPoint.x)
        return Direction::Right;
    else if (fromPoint.x > toPoint.x)
        return Direction::Left;
    else if (fromPoint.y > toPoint.y)
        return Direction::Up;
    return Direction::Down;
}