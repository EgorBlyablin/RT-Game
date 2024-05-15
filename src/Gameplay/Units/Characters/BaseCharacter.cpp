#include <chrono>
#include <iostream>

#include "Gameplay/Units/Characters/BaseCharacter.h"

using namespace std::chrono_literals;

BaseCharacter::BaseCharacter(sf::Vector2u position, unsigned int hp) : BaseUnit(position, hp)
{
}

void BaseCharacter::moveTo(sf::Vector2u targetPosition, std::function<bool(sf::Vector2u)> isTileFree,
                           bool calledFromAttackThread)
{
    // если приходит запрос на новое действие - завершаем действующие потоки
    if (calledFromAttackThread) // если требуется закрытие потока атаки (необходимо отключать, если перемещение
                                // вызывается из потока атаки)
        stopAttackThread();

    stopMovementThread(); // предыдущий поток перемещения в любом случае должен быть закрыт

    // инициализируем новый поток перемещения к указанной позиции
    movementThread = std::jthread([&, targetPosition, isTileFree](std::stop_token stopToken) {
        while (not stopToken.stop_requested() and position != targetPosition)
        {
            std::this_thread::sleep_for(std::chrono::duration<float>{1 / speed}); // запускаем временную отсечку

            if (stopToken.stop_requested()) // если за отсечку поступила отмена команды - прерываем цикл
                break;

            auto nextPosition = position; // координата следующей позиции

            if (abs(targetPosition.x - position.x) >= abs(targetPosition.y - position.y))
            {
                if (targetPosition.x > position.x)
                    nextPosition.x += 1;
                else
                    nextPosition.x -= 1;
            }
            else
            {
                if (targetPosition.y > position.y)
                    nextPosition.y += 1;
                else
                    nextPosition.y -= 1;
            }

            direction = getDirection(position, nextPosition);
            action = Action::Walk;
            position = nextPosition;
        }

        action = Action::Idle;
    });
}

void BaseCharacter::attack(std::unique_ptr<BaseUnit> *targetUnit, std::function<bool(sf::Vector2u)> isTileFree)
{
    // если приходит запрос на атаку новой цели - завершаем все потоки персонажа
    stopMovementThread();
    stopAttackThread();

    // инициализируем новый поток перемещения к указанной позиции
    attackThread = std::jthread([&, targetUnit, isTileFree](std::stop_token stopToken) {
        while (not stopToken.stop_requested() and targetUnit->get()->getHP() > 0)
        {
            moveTo(targetUnit->get()->getPosition(), isTileFree, false);

            while (movementThread.joinable() and BaseUnit::distance(this, targetUnit->get()) > 1)
                if (stopToken.stop_requested())
                    break;

            std::this_thread::sleep_for(std::chrono::duration<float>{1 / speed}); // запускаем временную отсечку

            if (stopToken.stop_requested()) // если за отсечку поступила отмена команды - прерываем цикл
                break;

            if (BaseUnit::distance(this, targetUnit->get()) == 1) // цель в поле досягаемости
            {
                direction = getDirection(position, targetUnit->get()->getPosition());
                action = Action::Attack;

                targetUnit->get()->setHP(targetUnit->get()->getHP() - damage);
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

void BaseCharacter::setSpeed(float speed)
{
    this->speed = speed;
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

void BaseCharacter::update()
{
    if (animationClock.getElapsedTime() >= animationTimeout[action])
    {
        animationFrame = (animationFrame + 1) % 4;
        animationClock.restart();
    }

    switch (action)
    {
    case Action::Idle:
        area.top = 0;
        area.left = (animationFrame % 2) * SPRITE_SIZE_PX;
        break;
    case Action::Walk:
        area.top = 0;
        area.left = (animationFrame + 1) * SPRITE_SIZE_PX;
        break;
    case Action::Attack:
        area.top = 4 * SPRITE_SIZE_PX;
        area.left += animationFrame * SPRITE_SIZE_PX;
    }

    switch (direction)
    {
    case Direction::Down:
        area.top = 0;
        break;
    case Direction::Up:
        area.top = 1 * SPRITE_SIZE_PX;
        break;
    case Direction::Right:
        area.top = 2 * SPRITE_SIZE_PX;
        break;
    case Direction::Left:
        area.top = 3 * SPRITE_SIZE_PX;
        break;
    }
}

void BaseCharacter::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    sf::Sprite sprite(texture, area);
    target.draw(sprite, states);
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