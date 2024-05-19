#ifndef BASE_H
#define BASE_H

#include "Gameplay/Units/Buildings/BaseBuilding.h"

/// @brief База игрока (игра оканчивается при ее уничтожении)
class Base : public BaseBuilding
{
  public:
    static const unsigned int maxHP = 1000;

    Base(sf::Vector2u position, unsigned int hp = maxHP);
    ~Base() = default; // требуется для умного указателя
};

#endif