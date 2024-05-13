#ifndef BASE_H
#define BASE_H

#include "Gameplay/Units/Buildings/BaseBuilding.h"

/// @brief База игрока (игра оканчивается при ее уничтожении)
class Base : public BaseBuilding
{
  protected:
    unsigned int hp = 500;

  public:
    Base(sf::Vector2u position);
    ~Base() = default; // требуется для умного указателя
};

#endif