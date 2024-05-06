#include <iostream>

#include "Gameplay/Characters/BaseCharacter.h"

#define SPRITE_SIZE_PX 16

BaseCharacter::BaseCharacter() : area(0, 0, SPRITE_SIZE_PX, SPRITE_SIZE_PX)
{
}

void BaseCharacter::update()
{
    if (animationClock.getElapsedTime() >= animationTimeout[action])
    {
        animationFrame = (animationFrame + 1) % 4;
        animationClock.restart();
    }

    switch (action)
    {
    case Action::Idle:
        area.top = 0;
        area.left = (animationFrame % 2) * SPRITE_SIZE_PX;
        break;
    case Action::Walk:
        area.top = 0;
        area.left = (animationFrame + 1) * SPRITE_SIZE_PX;
        break;
    case Action::Attack:
        area.top = 4 * SPRITE_SIZE_PX;
        area.left += animationFrame * SPRITE_SIZE_PX;
    }
}

sf::IntRect BaseCharacter::getArea() const
{
    return area;
}

void BaseCharacter::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    sf::Sprite sprite(texture, area);
    target.draw(sprite, states);
}