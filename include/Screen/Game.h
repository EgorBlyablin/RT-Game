#ifndef GAME_H
#define GAME_H

#include <vector>

#include "BaseScreen.h"
#include "Gameplay/Map/Map.h"
#include "UI/Button.h"

/// @brief Класс игры
class Game : public BaseScreen
{
  private:
    std::vector<Button> buttons; // кнопки

    Map map;

  public:
    Game();

    virtual void handleEvent(const sf::Event &event) override;
    virtual void update() override;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif