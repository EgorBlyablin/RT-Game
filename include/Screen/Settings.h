//
// Created by Иван on 27.04.2024.
//

#ifndef RTETRIS_SETTINGS_H
#define RTETRIS_SETTINGS_H

#include <functional>

#include <SFML/Graphics.hpp>

#include "BaseScreen.h"

class Settings : public BaseScreen
{
  public:
    Settings(sf::Vector2f windowSize, std::function<void(std::unique_ptr<BaseScreen>)> setScreen,
             sf::RenderWindow &window);

    void apply();

    void update() override;
    void handleEvent(const sf::Event &event) override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif // RTETRIS_SETTINGS_H
