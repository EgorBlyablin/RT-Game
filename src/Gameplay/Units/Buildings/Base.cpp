#include "Gameplay/Units/Buildings/Base.h"

Base::Base(sf::Vector2u position, unsigned int hp) : BaseBuilding(position, hp)
{
}

void Base::update()
{
}

void Base::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    sf::Sprite sprite(texture, area);
    target.draw(sprite, states);
}