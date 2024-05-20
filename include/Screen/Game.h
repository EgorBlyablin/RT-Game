#ifndef GAME_H
#define GAME_H

#include <functional>
#include <vector>

#include <SFML/System/Vector2.hpp>

#include "Gameplay/Camera.h"
#include "Gameplay/HUD.h"
#include "Gameplay/Map.h"
#include "Screen/BaseScreen.h"

/// @brief Класс игры
class Game : public BaseScreen
{
  private:
    Map map;       // игровое поле
    Camera camera; // камера
    HUD hud;

  public:
    Game(sf::Vector2f windowSize, std::function<void(std::unique_ptr<BaseScreen>)> setScreen, sf::RenderWindow &window);

    void handleEvent(const sf::Event &event) override;
    void update() override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif