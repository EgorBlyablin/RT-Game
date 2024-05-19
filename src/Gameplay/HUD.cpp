#include <iostream>
#include <sstream>
#include <string>

#include "Assets.h"
#include "Gameplay/HUD.h"

HUD::HUD(Map *map, Camera *camera, sf::Vector2f size) : map(map), camera(camera), size(size)
{
}

void HUD::handleEvent(const sf::Event &event, const Camera &camera)
{
}

void HUD::update()
{
}

void HUD::drawUnitInfo(sf::RenderTarget &target, sf::RenderStates states) const
{
    auto cursor = map->getCursor();

    sf::Sprite sprite((*cursor)->getTexture(), (*cursor)->getArea());
    sprite.scale(std::min(size.x, size.y) / (*cursor)->getArea().getSize().x * 0.9,
                 std::min(size.x, size.y) / (*cursor)->getArea().getSize().y * 0.9);
    sprite.setPosition((size.x - sprite.getGlobalBounds().getSize().x) / 2.f, 50.f);

    target.draw(sprite, states);

    auto hp = (*cursor)->getHP();
    auto maxHP = (*cursor)->getMaxHP();
    sf::RectangleShape hpBorder(sf::Vector2f(size.x * 0.8f, size.y * 0.1f));
    hpBorder.setPosition(size.x * 0.1f, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height);
    hpBorder.setOutlineColor(sf::Color::Black);
    hpBorder.setFillColor(sf::Color::Black);
    hpBorder.setOutlineThickness(2.f);

    sf::RectangleShape hpBar(sf::Vector2f(size.x * 0.8f * (hp / maxHP), size.y * 0.1f));
    hpBar.setPosition(hpBorder.getPosition());
    hpBar.setFillColor(sf::Color::Green);

    sf::Text hpText(std::to_string(hp) + '/' + std::to_string(maxHP), Assets::getInstance().font,
                    (int)hpBar.getSize().y / 2);
    hpText.setOrigin(hpText.getGlobalBounds().left, hpText.getGlobalBounds().top);
    hpText.setPosition(hpBar.getPosition() + (hpBar.getSize() - hpText.getGlobalBounds().getSize()) / 2.f);

    target.draw(hpBorder, states);
    target.draw(hpBar, states);
    target.draw(hpText, states);
}

void HUD::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    sf::RectangleShape background(size);
    background.setFillColor(sf::Color(149, 95, 32));
    background.setOutlineColor(sf::Color(129, 75, 22));
    background.setOutlineThickness(4.f);
    target.draw(background, states);

    if (map->getCursor() != nullptr and map->getCursor()->get() != nullptr)
        drawUnitInfo(target, states);
}