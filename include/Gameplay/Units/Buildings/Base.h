#ifndef BASE_H
#define BASE_H

#include "Gameplay/Units/Buildings/BaseBuilding.h"

/// @brief Класс базы игрока (игра оканчивается при ее уничтожении)
class Base : public BaseBuilding
{
  protected:
    unsigned int hp = 500;
};

#endif