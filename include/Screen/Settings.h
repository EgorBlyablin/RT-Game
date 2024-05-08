//
// Created by Иван on 27.04.2024.
//

#ifndef RTETRIS_SETTINGS_H
#define RTETRIS_SETTINGS_H


#include "BaseScreen.h"

class Settings: public BaseScreen
{
  private:
    static bool settingsActive;
  public:
    Settings();
    virtual void handleEvent(const sf::Event &event) override;
    virtual void update() override;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    static bool isSettingsActive();
    static void setSettingsActive(bool settingsActive);
};

#endif // RTETRIS_SETTINGS_H
