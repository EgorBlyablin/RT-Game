#include "Gameplay/Tiles/BaseTile.h"

BaseTile::BaseTile(const sf::Texture &texture, sf::IntRect area) : texture(texture), area(area)
{
}

sf::IntRect BaseTile::getArea() const
{
    return area;
}

void BaseTile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    sf::Sprite sprite(texture, area);

    sf::RectangleShape tileRect(sprite.getGlobalBounds().getSize());
    tileRect.setOutlineColor(sf::Color(0, 179, 74));
    tileRect.setOutlineThickness(1.f);
    tileRect.setFillColor(sf::Color::Transparent);

    target.draw(sprite, states);
    target.draw(tileRect, states);
}