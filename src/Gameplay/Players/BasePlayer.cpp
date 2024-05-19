#include <iostream>

#include "Gameplay/Players/BasePlayer.h"
#include "Gameplay/Units/Buildings/Base.h"
#include "Gameplay/Units/Characters/BaseCharacter.h"
#include "Utilities/AStar.h"

#define UNIT_CREATION_SECONDS 20
#define MAX_UNITS 5

std::vector<std::unique_ptr<BaseUnit>> &BasePlayer::getUnits()
{
    return units;
}

void BasePlayer::update()
{
    for (auto &unit : units)
        unit->update();
}
