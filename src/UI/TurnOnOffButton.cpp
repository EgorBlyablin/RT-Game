//
// Created by Иван on 14.05.2024.
//

#include <iostream>

#include "UI/TurnOnOffButton.h"

TurnOnOffButton::TurnOnOffButton(const sf::Vector2f &position, const sf::Vector2f &size,
                                 const sf::Font &font, const unsigned int characterSize,
                                 const std::pair<std::function<void(void)>, std::function<void(void)>> &callbacks)
    : Button(position, size, "OFF", font, characterSize), callbacks(callbacks)
{}

void TurnOnOffButton::updateColor()
{
    if (isPressed) // кнопка нажата
    {
        shape.setFillColor(backgroundColorOnClick);
        text.setFillColor(textColorOnClick);
    }
    else if (isHovered) // курсор наведен на кнопку
    {
        shape.setFillColor(backgroundColorOnHover);
        text.setFillColor(textColorOnHover);
    }
    else // стандартный вид кнопки
    {
        if(isTurnedOn){
            shape.setFillColor(backgroundColorOnHover);
            text.setFillColor(textColorOnHover);
        }
        else{
            shape.setFillColor(backgroundColor);
            text.setFillColor(textColor);
        }
    }
    if (isTurnedOn){
        text.setString("ON");
    }
    else{
        text.setString("OFF");
    }
}
void TurnOnOffButton::handleEvent(const sf::Event &event)
{
    switch (event.type)
    {
    case sf::Event::MouseButtonReleased: // кнопка отпущена
        if (event.mouseButton.button == sf::Mouse::Button::Left)
        {
            if (shape.getGlobalBounds().contains(
                    event.mouseButton.x,
                    event.mouseButton
                        .y)) // данная проверка проводится для того, чтобы случайно нажав на кнопку была возможность не
                             // активировать ее, если отвести курсор в другое место и только потом отпустить
            {
                isTurnedOn = !isTurnedOn;//смена состояния
                if(isTurnedOn){
                    callbacks.first();
                }
                else{
                    callbacks.second();
                }
                updateColor();
            }
            isPressed = false;
            if (isHovered){//сделал так, потому что после смены экрана текущая функция продолжает выполняться, но при этом
                //при вызове любой функции кнопки кидается segmentation fault, то есть метод updateColor() вызывается с исключением
                shape.setFillColor(backgroundColorOnHover);
                text.setFillColor(textColorOnHover);
            }
        }
        break;
    case sf::Event::MouseButtonPressed: // кнопка нажата
        isPressed = (event.mouseButton.button == sf::Mouse::Button::Left) and
                    (shape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y));
        updateColor();
        break;
    case sf::Event::MouseMoved: // положение курсора изменилось
        isHovered = shape.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y);
        updateColor();
        break;
    default:
        updateColor();
        break;
    }
}
