#include <iostream>

#include "Gameplay/Units/BaseUnit.h"

#define HP_BAR_OUTLINE 0.5f

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
    sprite.setScale(1 - 2.f / sprite.getGlobalBounds().width, 1 - 2.f / sprite.getGlobalBounds().height);
    sprite.move(0.5f, 0.5f);
    target.draw(sprite, states);

    if (hp < maxHP)
    {
        sf::RectangleShape background(
            sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height / 8));
        background.setFillColor(sf::Color::Black);

        float hpRatio = (float)hp / maxHP;
        sf::RectangleShape bar(sf::Vector2f(background.getGlobalBounds().width * hpRatio - HP_BAR_OUTLINE * 2,
                                            background.getGlobalBounds().height - HP_BAR_OUTLINE * 2));
        bar.setFillColor(sf::Color::Green);

        background.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);
        bar.setPosition(background.getPosition() + sf::Vector2f(HP_BAR_OUTLINE, HP_BAR_OUTLINE));

        target.draw(background, states);
        target.draw(bar, states);
    }
}

unsigned int BaseUnit::distance(sf::Vector2u first, sf::Vector2u second)
{
    auto delta = second - first;

    return abs(delta.x) + abs(delta.y);
}