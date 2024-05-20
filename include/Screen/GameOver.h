#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include <functional>

#include <SFML/Graphics.hpp>

#include "BaseScreen.h"

/// @brief Экран конца игры
/// @details Этот экран запускается при уничтожении одной из баз
class GameOver : public BaseScreen
{
  private:
    std::string message;

  public:
    GameOver(sf::Vector2f windowSize, std::function<void(std::unique_ptr<BaseScreen>)> setScreen,
             sf::RenderWindow &window, std::string message);

    void handleEvent(const sf::Event &event) override;
    void update() override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif