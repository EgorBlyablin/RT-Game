//
// Created by Иван on 27.04.2024.
//

#ifndef RTETRIS_SETTINGS_H
#define RTETRIS_SETTINGS_H
#include "BaseScreen.h"

class Settings: public BaseScreen
{
  public:
    Settings();
    void handleEvent(const sf::Event &event) override;
    void update() override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif // RTETRIS_SETTINGS_H
