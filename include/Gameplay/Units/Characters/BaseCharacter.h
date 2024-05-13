#ifndef BASE_CHARACTERS_H
#define BASE_CHARACTERS_H

#include <functional>
#include <map>
#include <memory>
#include <thread>

#include <SFML/Graphics.hpp>

#include "Gameplay/Units/BaseUnit.h"

class BaseCharacter : public BaseUnit
{
  protected:
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

    float speed = 3.f; // скорость перемещения - число проходимых за секунду клеток

    const sf::Texture &texture = Assets::getInstance().defaultCharacter;

    Action action = Action::Idle; // текущее действие

    unsigned int animationFrame = 0; // кадр анимации
    sf::Clock animationClock;        // таймер переключения кадров

    std::jthread movementThread; // поток перемещения

  public:
    BaseCharacter(sf::Vector2u position);
    ~BaseCharacter() = default; // требуется для умного указателя

    virtual void moveTo(sf::Vector2u targetPosition,
                        std::function<bool(sf::Vector2u)> isTileFree); // перемещение в указанную позицию

    virtual float getSpeed() const;
    virtual void setSpeed(float speed);

    virtual void update(); // обновление состояний
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override; // отрисовка клетки
};

#endif