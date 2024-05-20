//
// Created by Иван on 27.04.2024.
//
#include <iostream>

#include "Application.h"
#include "Assets.h"
#include "Screen/Menu.h"
#include "Screen/Settings.h"
#include "UI/SwitchButton.h"
#include "UI/TurnOnOffButton.h"

Settings::Settings(sf::Vector2f windowSize, std::function<void(std::unique_ptr<BaseScreen>)> setScreen,
                   sf::RenderWindow &window)
    : BaseScreen(windowSize, setScreen)
{
    std::map<std::string, std::function<void(void)>> callBacks{
        {"640x350", [&window] { window.setSize(sf::Vector2u(640, 350)); }},
        {"880x600", [&window] { window.setSize(sf::Vector2u(880, 600)); }},
        {"1024x768", [&window] { window.setSize(sf::Vector2u(1024, 768)); }}};

    std::unique_ptr<SwitchButton> resolutionButton = std::make_unique<SwitchButton>(
        sf::Vector2f(windowSize.x * 0.425, windowSize.y * 0.1), sf::Vector2f(windowSize.x * 0.15, windowSize.y * 0.1),
        "Resolution", Assets::getInstance().font, windowSize.y * 0.1 / 4, callBacks);
    resolutionButton->setBackgroundColor(sf::Color(160, 160, 160), sf::Color(50, 50, 50), sf::Color(90, 90, 90));
    resolutionButton->setTextColor(sf::Color(255, 255, 255));

    std::unique_ptr<Button> applyButton = std::make_unique<Button>(
        sf::Vector2f(windowSize.x * 0.425, windowSize.y * 0.2), sf::Vector2f(windowSize.x * 0.15, windowSize.y * 0.1),
        "Apply", Assets::getInstance().font, 30 * windowSize.y / 800, [this] { this->apply(); });
    applyButton->setBackgroundColor(sf::Color(160, 160, 160), sf::Color(50, 50, 50), sf::Color(90, 90, 90));
    applyButton->setTextColor(sf::Color(255, 255, 255));

    std::unique_ptr<Button> exitButton = std::make_unique<Button>(
        sf::Vector2f(windowSize.x * 0.425, windowSize.y * 0.3), sf::Vector2f(windowSize.x * 0.15, windowSize.y * 0.1),
        "Exit", Assets::getInstance().font, 30 * windowSize.y / 800, [windowSize, setScreen, &window] {
            setScreen(std::make_unique<Menu>(
                windowSize,
                [windowSize, setScreen](std::unique_ptr<BaseScreen> newScreen) { setScreen(std::move(newScreen)); },
                window));
        });
    exitButton->setBackgroundColor(sf::Color(160, 160, 160), sf::Color(50, 50, 50), sf::Color(90, 90, 90));
    exitButton->setTextColor(sf::Color(255, 255, 255));

    buttons.push_back(std::move(resolutionButton));
    buttons.push_back(std::move(applyButton));
    buttons.push_back(std::move(exitButton));
}

void Settings::handleEvent(const sf::Event &event)
{
    for (auto &button : buttons) // передача события каждой кнопке для его обработки
    {
        if (not isActive) // чтобы кнопки перестали обрабатываться, если меню настроек не является текущим экраном
            break;
        button->handleEvent(event);
    }
}

void Settings::update()
{
}

void Settings::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform(); // учет трансформаций экрана при отрисовке всех ее элементов

    for (auto &button : buttons) // отрисовка всех кнопок
        target.draw(*button, states);
}

void Settings::apply()
{
    for (auto &button : buttons)
        button->apply();
}
