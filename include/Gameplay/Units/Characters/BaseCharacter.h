#ifndef BASE_CHARACTERS_H
#define BASE_CHARACTERS_H

#include <functional>
#include <map>
#include <memory>
#include <thread>

#include <SFML/Graphics.hpp>

#include "Gameplay/Units/BaseUnit.h"

/// @brief Базовый класс персонажа
class BaseCharacter : public BaseUnit
{
  private:
    static const unsigned int initialHP = 100;
    static const unsigned int damage = 20;

  protected:
    enum class Action // текущее действие
    {
        Idle,
        Walk,
        Attack
    };

    enum class Direction // направление взгляда
    {
        Down,
        Up,
        Right,
        Left
    };

    std::map<Action, sf::Time> animationTimeout{
        {Action::Idle, sf::milliseconds(1000)},
        {Action::Walk, sf::milliseconds(200)},
        {Action::Attack, sf::milliseconds(100)}}; // время перехода к следующему кадру анимации

    float speed = 3.f; // скорость перемещения - число проходимых за секунду клеток

    const sf::Texture &texture = Assets::getInstance().defaultCharacter;

    Action action = Action::Idle;          // текущее действие
    Direction direction = Direction::Down; // направление взгляда

    unsigned int animationFrame = 0; // кадр анимации
    sf::Clock animationClock;        // таймер переключения кадров

    std::jthread movementThread; // поток перемещения
    std::jthread attackThread;   // поток атаки

  public:
    BaseCharacter(sf::Vector2u position, unsigned int hp = initialHP);
    ~BaseCharacter() = default; // требуется для умного указателя

    virtual void moveTo(sf::Vector2u targetPosition, std::function<bool(sf::Vector2u)> isTileFree,
                        bool calledFromAttackThread = true); // перемещение в указанную позицию
    virtual void attack(std::unique_ptr<BaseUnit> *targetUnit, std::function<bool(sf::Vector2u)> isTileFree);

    virtual float getSpeed() const;
    virtual void setSpeed(float speed);

    void stopMovementThread();
    void stopAttackThread();

    virtual void update(); // обновление состояний
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override; // отрисовка клетки

    static Direction getDirection(sf::Vector2u fromPoint, sf::Vector2u toPoint);
};

#endif