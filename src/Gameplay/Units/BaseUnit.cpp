#include "Gameplay/Units/BaseUnit.h"

BaseUnit::BaseUnit(sf::Vector2u position) : position(position)
{
}

sf::Vector2u BaseUnit::getPosition() const
{
    return position;
}

void BaseUnit::setPosition(sf::Vector2u position)
{
    this->position = position;
}

sf::IntRect BaseUnit::getArea() const
{
    return area;
}