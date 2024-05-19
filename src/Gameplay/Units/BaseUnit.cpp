#include <iostream>

#include "Gameplay/Units/BaseUnit.h"

BaseUnit::BaseUnit(sf::Vector2u position, unsigned int hp, unsigned int maxHP, const sf::Texture &texture,
                   sf::IntRect area)
    : position(position), hp(hp), maxHP(maxHP), texture(texture), area(area)
{
}

sf::Vector2u BaseUnit::getPosition() const
{
    return position;
}

unsigned int BaseUnit::getHP() const
{
    return hp;
}

unsigned int BaseUnit::getMaxHP() const
{
    return maxHP;
}

const sf::Texture &BaseUnit::getTexture() const
{
    return texture;
}

sf::IntRect BaseUnit::getArea() const
{
    return area;
}

void BaseUnit::setPosition(sf::Vector2u position)
{
    this->position = position;
}

void BaseUnit::setHP(unsigned int hp)
{
    this->hp = std::max(0u, hp);
}

void BaseUnit::update()
{
}

void BaseUnit::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    sf::Sprite sprite(texture, area);
    target.draw(sprite, states);
}

unsigned int BaseUnit::distance(sf::Vector2u first, sf::Vector2u second)
{
    auto delta = second - first;

    return abs(delta.x) + abs(delta.y);
}