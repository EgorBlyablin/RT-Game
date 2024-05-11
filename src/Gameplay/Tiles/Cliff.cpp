#include "Gameplay/Tiles/Cliff.h"

sf::IntRect Cliff::getArea() const
{
    return area;
}

void Cliff::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    sf::Sprite sprite(texture, area);
    target.draw(sprite, states);
}