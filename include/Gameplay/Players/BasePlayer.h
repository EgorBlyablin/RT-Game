#ifndef BASE_PLAYER_H
#define BASE_PLAYER_H

#include <vector>

#include <SFML/System.hpp>

#include "Gameplay/Camera.h"
#include "Gameplay/Units/BaseUnit.h"
#include "Gameplay/Units/Buildings/Base.h"

class BasePlayer
{
  protected:
    std::vector<std::unique_ptr<BaseUnit>> units; // вектор умных указателей на юнитов
    sf::Clock newUnitTimer;                       // таймер создания нового юнита

  public:
    BasePlayer() = default;
    ~BasePlayer() = default;

    const std::vector<std::unique_ptr<BaseUnit>> &getUnits() const;
    std::vector<std::unique_ptr<BaseUnit>> &getUnits();

    virtual void update();
};

#endif