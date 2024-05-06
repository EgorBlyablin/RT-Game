#ifndef BASE_CHARACTERS_H
#define BASE_CHARACTERS_H

#include <map>

#include <SFML/Graphics.hpp>

#include "../../Assets.h"

class BaseCharacter : public sf::Drawable, public sf::Transformable
{
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

  private:
    const sf::Texture &texture = Assets::getInstance().defaultCharacter;
    sf::IntRect area; // участок текстуры для отрисовки

    Direction direction = Direction::Down;
    Action action = Action::Idle;

    unsigned int animationFrame = 0;
    sf::Clock animationClock;

  public:
    BaseCharacter();
    ~BaseCharacter() = default; // требуется для умного указателя

    virtual void update(); // обновление состояний

    virtual sf::IntRect getArea() const; // получение области текстуры - требуется для масштабирования

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override; // отрисовка клетки
};

#endif