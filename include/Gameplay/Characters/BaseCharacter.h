#ifndef BASE_CHARACTERS_H
#define BASE_CHARACTERS_H

#include <functional>
#include <map>
#include <memory>
#include <thread>

#include <SFML/Graphics.hpp>

#include "Assets.h"

#define SPRITE_SIZE_PX 16

class BaseCharacter : public sf::Drawable, public sf::Transformable
{
  private:
    enum class Direction // направление взгляда
    {
        Down,
        Up,
        Right,
        Left
    };

    enum class Action // текущее действие
    {
        Idle,
        Walk,
        Attack
    };

    std::map<Action, sf::Time> animationTimeout{
        {Action::Idle, sf::milliseconds(1000)},
        {Action::Walk, sf::milliseconds(200)},
        {Action::Attack, sf::milliseconds(100)}}; // время перехода к следующему кадру анимации

    sf::Vector2u position; // позиция в клеточном поле
    float speed = 3.f; // скорость перемещения - число проходимых за секунду клеток

    const sf::Texture &texture = Assets::getInstance().defaultCharacter;
    sf::IntRect area = sf::IntRect(0, 0, SPRITE_SIZE_PX, SPRITE_SIZE_PX); // участок текстуры для отрисовки

    Direction direction = Direction::Down; // направление взгляда
    Action action = Action::Idle;          // текущее действие

    unsigned int animationFrame = 0; // кадр анимации
    sf::Clock animationClock;        // таймер переключения кадров

    std::jthread movementThread; // поток перемещения

  public:
    BaseCharacter(sf::Vector2u position);
    ~BaseCharacter() = default; // требуется для умного указателя

    virtual void moveTo(sf::Vector2u targetPosition,
                        std::function<bool(sf::Vector2u)> isTileFree); // перемещение в указанную позицию

    sf::Vector2u getPosition() const;
    void setPosition(sf::Vector2u position);
    virtual float getSpeed() const;
    virtual void setSpeed(float speed);

    virtual sf::IntRect getArea() const; // получение области текстуры - требуется для масштабирования

    virtual void update(); // обновление состояний
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override; // отрисовка клетки
};

#endif