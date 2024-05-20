#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include <functional>

#include <SFML/Graphics.hpp>

#include "BaseScreen.h"

/// @brief Экран меню
/// @details Этот экран запускается при запуске приложения
class Menu : public BaseScreen
{
  public:
    Menu(sf::Vector2f windowSize, std::function<void(std::unique_ptr<BaseScreen>)> setScreen, sf::RenderWindow &window);

    void handleEvent(const sf::Event &event) override;
    void update() override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif