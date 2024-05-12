//
// Created by Иван on 04.05.2024.
//

#include <iostream>

#include "Application.h"
#include "UI/SwitchButton.h"

SwitchButton::SwitchButton(const sf::Vector2f &position, const sf::Vector2f &size, const std::string &text, const sf::Font &font,
                           const unsigned int characterSize,const std::map<std::string, std::function<void(void)>> &callbacks) : callbacks(callbacks)
{



    this->choice = this->callbacks.begin();


    shape.setSize(size); // установка размеров заднего фона

    this->text.setString(text); // установка текста названия кнопки
    this->text.setFont(font);
    this->text.setCharacterSize(characterSize); // установка размера текста

    info.setSize(sf::Vector2f(80,40));

    this->infoText.setString(this->callbacks.begin()->first);
    this->infoText.setFont(font);
    this->infoText.setCharacterSize(characterSize-6);


    info.setPosition(sf::Vector2f(position.x+size.x/2+26, position.y)); // позиционирование заднего фона(делается здесь для учета заданного размера кнопки)

    setPosition(position); // позиционирование названия кнопки


    ///левая и правая кнопки перемещения и кнопка подтверждения
    left = Button(sf::Vector2f(position.x+size.x/2+3,position.y), sf::Vector2f(20,20), "<-", font, 20,
                  [this]{
                      //итератор должен декрементироваться, либо же перемещаться в конец контейнера, если достигнуто начало
                      if (this->choice == this->callbacks.begin()){
                          this->choice = std::next(this->callbacks.end(), -1);
                      }
                      else{
                          this->choice = std::next(this->choice, -1);
                      }
                  });




    right = Button(sf::Vector2f(position.x+size.x/2+3 +83 ,position.y), sf::Vector2f(20,20), "->", font, 20,
                   [this]{
                       //итератор должен инкрементироваться, либо же перемещаться в начало контейнера, если достигнут конец
                       this->choice = (this->choice == std::next(this->callbacks.end(), -1))? this->callbacks.begin(): std::next(this->choice, 1);
                   });


}
void SwitchButton::updateColor()
{
    shape.setFillColor(backgroundColor);
    text.setFillColor(textColor);

    info.setFillColor(backgroundColor);
    infoText.setFillColor(textColor);

    infoText.setString(choice->first);
}
void SwitchButton::handleEvent(const sf::Event &event)
{
    left.handleEvent(event);
    right.handleEvent(event);


    updateColor();
}
void SwitchButton::setPosition(sf::Vector2f position)
{
    Button::setPosition(position);




    infoText.setOrigin(
        infoText.getGlobalBounds().left,
        infoText.getGlobalBounds().top); // обновление исходной точки текста (т.к. размеры текста могли измениться)
    infoText.setPosition(info.getPosition() +
                     (info.getSize() - sf::Vector2f(infoText.getGlobalBounds().width, infoText.getGlobalBounds().height)) /
                         2.f); // центрирование текста на кнопке
}
void SwitchButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    Button::draw(target, states);
    left.draw(target, states);
    right.draw(target, states);


    target.draw(info);
    target.draw(infoText);

}

void SwitchButton::apply()
{
    this->choice->second();
}
