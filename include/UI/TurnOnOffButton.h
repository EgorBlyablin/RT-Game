//
// Created by Иван on 14.05.2024.
//

#include "UI/Button.h"

#ifndef RTETRIS_TURNONOFFBUTTON_H
#define RTETRIS_TURNONOFFBUTTON_H

class TurnOnOffButton : public Button
{
  private:
    std::pair<std::function<void(void)>, std::function<void(void)>> callbacks; // первый элемент - выкл;

    bool isTurnedOn = false;

  public:
    TurnOnOffButton(const sf::Vector2f &position, const sf::Vector2f &size, const sf::Font &font,
                    const unsigned int characterSize,
                    const std::pair<std::function<void(void)>, std::function<void(void)>> &callbacks);

    TurnOnOffButton(const sf::Vector2f &position, const sf::Vector2f &size, const sf::Font &font,
                    const unsigned int characterSize,
                    const std::pair<std::function<void(void)>, std::function<void(void)>> &callbacks, bool turnedOn)
        : TurnOnOffButton(position, size, font, characterSize, callbacks)
    {
        this->isTurnedOn = turnedOn;
    }

    void updateColor() override;
    void handleEvent(const sf::Event &event) override;
};

#endif // RTETRIS_TURNONOFFBUTTON_H
