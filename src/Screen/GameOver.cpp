#include <iostream>
#include <stdlib.h>

#include "Assets.h"
#include "Screen/GameOver.h"
#include "Screen/Menu.h"
#include "Screen/Settings.h"
#include "UI/Button.h"

GameOver::GameOver(sf::Vector2f windowSize, std::function<void(std::unique_ptr<BaseScreen>)> setScreen,
                   sf::RenderWindow &window, std::string message)
    : BaseScreen(windowSize, setScreen, window), message(message)
{
    std::unique_ptr<Button> exitButton = std::make_unique<Button>(
        sf::Vector2f(windowSize.x * 0.425, windowSize.y * 0.4), sf::Vector2f(windowSize.x * 0.15, windowSize.y * 0.1),
        "Exit", Assets::getInstance().font, 30 * windowSize.y / 800, [] { exit(0); });
    exitButton->setBackgroundColor(sf::Color(160, 160, 160), sf::Color(50, 50, 50), sf::Color(90, 90, 90));
    exitButton->setTextColor(sf::Color(255, 255, 255));

    buttons.push_back(std::move(exitButton));
}

void GameOver::handleEvent(const sf::Event &event) // передача события каждой кнопке для его обработки
{
    if (isActive)
        for (auto &button : buttons)
            button->handleEvent(event);
}

void GameOver::update()
{
}

void GameOver::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform(); // учет трансформаций экрана при отрисовке всех ее элементов

    for (auto &button : buttons) // отрисовка всех кнопок
        target.draw(*button, states);

    sf::Text text(message, Assets::getInstance().font);
    text.setPosition((window.getSize().x - text.getGlobalBounds().getSize().x) / 2.f, window.getSize().y * 0.1f);

    target.draw(text, states);
}
