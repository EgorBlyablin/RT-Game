//
// Created by Иван on 04.05.2024.
//

#include <iostream>

#include "Application.h"
#include "UI/SwitchButton.h"

SwitchButton::SwitchButton(const sf::Vector2f &position, const sf::Vector2f &size, const std::string &text,
                           const sf::Font &font, const unsigned int characterSize,
                           const std::map<std::string, std::function<void(void)>> &callbacks)
    : Button(sf::Vector2f(position.x + size.x * 0.2, position.y), sf::Vector2f(size.x * 0.6, size.y), text, font,
             characterSize),
      callbacks(callbacks)
{
    this->choice = this->callbacks.begin();

    /// левая и правая кнопки перемещения и кнопка подтверждения
    left = Button(position, sf::Vector2f(size.x * 0.2, size.y), "<", font, characterSize - 8, [this] {
        // итератор должен декрементироваться, либо же перемещаться в конец контейнера, если достигнуто
        // начало
        if (this->choice == this->callbacks.begin())
            this->choice = std::next(this->callbacks.end(), -1);
        else
            this->choice = std::next(this->choice, -1);
    });

    right = Button(sf::Vector2f(position.x + size.x * 0.8, position.y), sf::Vector2f(size.x * 0.2, size.y), ">", font,
                   characterSize - 8, [this] {
                       // итератор должен инкрементироваться, либо же перемещаться в начало контейнера, если достигнут
                       // конец
                       if (std::next(this->choice) == this->callbacks.end())
                           this->choice = this->callbacks.begin();
                       else
                           this->choice = std::next(this->choice, 1);
                   });
}

void SwitchButton::updateColor()
{
    left.updateColor();
    right.updateColor();
}

void SwitchButton::apply()
{
    this->choice->second();
}

void SwitchButton::handleEvent(const sf::Event &event)
{
    left.handleEvent(event);
    right.handleEvent(event);
}

void SwitchButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(left, states);
    target.draw(right, states);

    sf::RectangleShape textShape(shape.getSize());
    textShape.setFillColor(backgroundColor);
    sf::Text text(this->choice->first, *this->text.getFont(), this->text.getCharacterSize());
    text.setFillColor(textColor);

    textShape.setPosition(shape.getPosition());
    text.setOrigin(text.getGlobalBounds().left, text.getGlobalBounds().top);
    text.setPosition(textShape.getPosition() + (textShape.getSize() - text.getGlobalBounds().getSize()) / 2.f);

    target.draw(textShape, states);
    target.draw(text, states);
}
