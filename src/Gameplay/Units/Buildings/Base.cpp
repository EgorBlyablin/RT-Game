#include "Gameplay/Units/Buildings/Base.h"

Base::Base(sf::Vector2u position, unsigned int hp) : BaseBuilding(position, hp, Base::maxHP)
{
}