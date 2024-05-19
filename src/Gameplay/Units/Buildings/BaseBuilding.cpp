#include "Gameplay/Units/Buildings/BaseBuilding.h"
#include "Assets.h"

BaseBuilding::BaseBuilding(sf::Vector2u position, unsigned int hp, unsigned int maxHP,
                           const sf::Texture &texture, sf::IntRect area)
    : BaseUnit(position, hp, maxHP, texture, area)
{
}
