#include "Gameplay/Units/Buildings/Base.h"

Base::Base(sf::Vector2u position) : BaseBuilding(position)
{
}

void Base::moveTo(sf::Vector2u targetPosition,
                  std::function<bool(sf::Vector2u)> isTileFree) // перемещение в указанную позицию
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