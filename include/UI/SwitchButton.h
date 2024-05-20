//
// Created by Иван on 04.05.2024.
//

#ifndef RTETRIS_SWITCHBUTTON_H
#define RTETRIS_SWITCHBUTTON_H

#include <map>

#include "Button.h"

/// @brief Класс кнопки c выбором
/// @details Выполняет отрисовку кнопки с двумя стрелочками справа и слева в соответствии с ее состоянием,
/// изменяет ее состояние в соответствии с событиями,
/// вызывает callback-функцию
///@todo не прокручивается выбор, прога вылетает с исключением, когда выбор должен перекрутиться в начало/конец
class SwitchButton : public Button
{
  protected:
    std::map<std::string, std::function<void(void)>> callbacks;
    std::map<std::string, std::function<void(void)>>::iterator choice;

    Button left;
    Button right;

  public:
    SwitchButton() = default;
    SwitchButton(const sf::Vector2f &position, const sf::Vector2f &size, const std::string &text, const sf::Font &font,
                 const unsigned int characterSize, const std::map<std::string, std::function<void(void)>> &callbacks);
    SwitchButton(const sf::Vector2f &size, const std::string &text, const sf::Font &font,
                 const unsigned int characterSize, const std::map<std::string, std::function<void(void)>> &callbacks)
        : SwitchButton(sf::Vector2f(0, 0), size, text, font, characterSize, callbacks)
    {
    }

    void updateColor() override;
    void apply();

    void handleEvent(const sf::Event &event) override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif // RTETRIS_SWITCHBUTTON_H
