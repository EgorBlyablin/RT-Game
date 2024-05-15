#include <chrono>
#include <iostream>

#include "Gameplay/Units/Characters/BaseCharacter.h"

using namespace std::chrono_literals;

BaseCharacter::BaseCharacter(sf::Vector2u position, unsigned int hp) : BaseUnit(position, hp)
{
}

void BaseCharacter::moveTo(sf::Vector2u targetPosition, std::function<bool(sf::Vector2u)> isTileFree)
{
    if (movementThread.joinable()) // если приходит запрос на новое перемещение - отправляем запрос на завершение потока
                                   // и ждем его завершения
    {
        movementThread.request_stop();
        movementThread.join();
    }

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
                {
                    direction = Direction::Right;
                    nextPosition.x += 1;
                }
                else
                {
                    direction = Direction::Left;
                    nextPosition.x -= 1;
                }
            }
            else
            {
                if (targetPosition.y > position.y)
                {
                    direction = Direction::Down;
                    nextPosition.y += 1;
                }
                else
                {
                    direction = Direction::Up;
                    nextPosition.y -= 1;
                }
            }

            action = Action::Walk;
            this->setPosition(nextPosition);
        }

        direction = Direction::Down;
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