#include <iostream>

#include "Gameplay/Players/BasePlayer.h"
#include "Gameplay/Units/BaseUnit.h"

const std::vector<std::unique_ptr<BaseUnit>> &BasePlayer::getUnits() const
{
    return units;
}

std::vector<std::unique_ptr<BaseUnit>> &BasePlayer::getUnits()
{
    return units;
}

void BasePlayer::update()
{
    for (auto &unit : units)
        unit->update();
}
