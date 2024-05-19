#ifndef BASE_BUILDING_H
#define BASE_BUILDING_H

#include "Gameplay/Units/BaseUnit.h"

class BaseBuilding : public BaseUnit
{
  public:
    static const unsigned int maxHP = 100;

    BaseBuilding(sf::Vector2u position, unsigned int hp = maxHP, unsigned int maxHP = BaseBuilding::maxHP, const sf::Texture &texture = Assets::getInstance().defaultBuilding,
                 sf::IntRect area = sf::IntRect(0, 0, SPRITE_SIZE_PX, SPRITE_SIZE_PX));
    ~BaseBuilding() = default; // требуется для умного указателя
};

#endif