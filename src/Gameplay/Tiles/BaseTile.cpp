#include "Gameplay/Tiles/BaseTile.h"

sf::IntRect BaseTile::getArea() const
{
    return area;
}

void BaseTile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    sf::Sprite sprite(
        texture,
        area); // создание спрайта для отрисовки (не влияет на производительность, поэтому нет смысла хранить в объекте)
    target.draw(sprite, states);
}