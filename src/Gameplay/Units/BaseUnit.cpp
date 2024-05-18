#include <iostream>

#include "Gameplay/Units/BaseUnit.h"

BaseUnit::BaseUnit(sf::Vector2u position, unsigned int hp) : position(position), hp(hp)
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

unsigned int BaseUnit::getHP() const
{
    return hp;
}

void BaseUnit::setHP(unsigned int hp)
{
    this->hp = std::max(0u, hp);
}

sf::IntRect BaseUnit::getArea() const
{
    return area;
}

unsigned int BaseUnit::distance(sf::Vector2u first, sf::Vector2u second)
{
    auto delta = second - first;

    return abs(delta.x) + abs(delta.y);
}