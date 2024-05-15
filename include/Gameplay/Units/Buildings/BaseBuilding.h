#ifndef BASE_BUILDING_H
#define BASE_BUILDING_H

#include "Gameplay/Units/BaseUnit.h"

class BaseBuilding : public BaseUnit
{
  private:
    static const unsigned int initialHP = 100;

  protected:
    const sf::Texture &texture = Assets::getInstance().defaultBuilding;
    sf::IntRect area = sf::IntRect(0, 0, SPRITE_SIZE_PX, SPRITE_SIZE_PX); // участок текстуры для отрисовки

  public:
    BaseBuilding(sf::Vector2u position, unsigned int hp = initialHP);
    ~BaseBuilding() = default; // требуется для умного указателя
};

#endif