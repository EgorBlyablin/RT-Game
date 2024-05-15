#ifndef BASE_H
#define BASE_H

#include "Gameplay/Units/Buildings/BaseBuilding.h"

/// @brief База игрока (игра оканчивается при ее уничтожении)
class Base : public BaseBuilding
{
  private:
    static const unsigned int initialHP = 1000;

  public:
    Base(sf::Vector2u position, unsigned int hp = initialHP);
    ~Base() = default; // требуется для умного указателя

    virtual void update() override; // обновление состояний
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override; // отрисовка клетки
};

#endif