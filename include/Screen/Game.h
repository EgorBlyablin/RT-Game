#ifndef GAME_H
#define GAME_H

#include <vector>

#include <SFML/System/Vector2.hpp>

#include "Gameplay/Camera.h"
#include "Gameplay/Map.h"
#include "Screen/BaseScreen.h"
#include "UI/Button.h"

/// @brief Класс игры
class Game : public BaseScreen
{
  private:
    std::vector<Button> buttons; // кнопки

    Map map;       // игровое поле
    Camera camera; // камера

  public:
    Game(sf::Vector2f windowSize);

    virtual void handleEvent(const sf::Event &event) override;
    virtual void update() override;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif