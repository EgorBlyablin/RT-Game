#ifndef BASE_CHARACTERS_H
#define BASE_CHARACTERS_H

#include <SFML/Graphics.hpp>

#include "../../Assets.h"

class BaseCharacter : public sf::Drawable, public sf::Transformable
{
    enum class Direction
    {
        Down,
        Up,
        Right,
        Left
    };

    enum class Action
    {
        Idle,
        Walk,
        Attack
    };

  private:
    const sf::Texture &texture = Assets::getInstance().defaultTexture;

    Direction direction = Direction::Down;
    Action action = Action::Idle;
    int actionFrame = 0;

  public:
    BaseCharacter() = default;
    ~BaseCharacter() = default; // требуется для умного указателя

    virtual sf::IntRect getArea() const; // получение области текстуры - требуется для масштабирования

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override; // отрисовка клетки
};

#endif