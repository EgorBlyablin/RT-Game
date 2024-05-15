#include "Gameplay/Players/BasePlayer.h"
#include "Gameplay/Units/Buildings/Base.h"
#include "Gameplay/Units/Characters/BaseCharacter.h"

std::vector<std::unique_ptr<BaseUnit>> &BasePlayer::getUnits()
{
    return units;
}

void BasePlayer::update()
{
    for (auto &unit : units)
        unit->update();
}
