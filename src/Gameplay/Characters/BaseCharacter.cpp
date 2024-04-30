#include "Gameplay/Characters/BaseCharacter.h"

#define SPRITE_SIZE_PX 16

sf::IntRect BaseCharacter::getArea() const
{
    sf::IntRect area(0, 0, SPRITE_SIZE_PX, SPRITE_SIZE_PX);

    switch (action)
    {
    case Action::Idle:
        area.left = actionFrame % 2;
        area.top = 0;
        break;
    case Action::Walk:
        area.top = 0;
        break;
    case Action::Attack:
        area.top = 4 * SPRITE_SIZE_PX;
    }

    return area;
}

void BaseCharacter::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    sf::Sprite sprite(texture, getArea());
    target.draw(sprite, states);
}