#include "Gameplay/Players/Player.h"
#include "Gameplay/Units/Characters/BaseCharacter.h"

Player::Player() : BasePlayer()
{
    auto base = std::make_unique<Base>(sf::Vector2u(0, 0));
    auto character = std::make_unique<BaseCharacter>(sf::Vector2u(1, 1));

    units.push_back(std::move(base));
    units.push_back(std::move(character));

    this->base = &base;
}

void Player::handleEvent(const sf::Event &event, const Camera &camera)
{
}