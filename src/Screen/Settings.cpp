//
// Created by Иван on 27.04.2024.
//
#include <iostream>

#include "Screen/Settings.h"
#include "Assets.h"
#include "Screen/Menu.h"
#include "Application.h"


bool Settings::settingsActive = false;

Settings::Settings()
{
    settingsActive = true;

    std::unique_ptr<Button> exitButton = std::make_unique<Button>(
        sf::Vector2f(200, 50), "Main menu", Assets::getInstance().font, 30, []
        {
            auto s = new Menu();
            Application::getInstance().setCurrentScreen(s);
            settingsActive = false;
        });
    exitButton->setBackgroundColor(sf::Color(160, 160, 160), sf::Color(50, 50, 50), sf::Color(90, 90, 90));
    exitButton->setTextColor(sf::Color(255, 255, 255));

    std::unique_ptr<Button> resolutionButton = std::make_unique<Button>(
        sf::Vector2f(0, 50), sf::Vector2f(200, 50), "Resolution", Assets::getInstance().font, 30, [] { std::cout << "resolution\n"; });
    resolutionButton->setBackgroundColor(sf::Color(160, 160, 160), sf::Color(50, 50, 50), sf::Color(90, 90, 90));
    resolutionButton->setTextColor(sf::Color(255, 255, 255));

    buttons.push_back(std::move(exitButton));
    buttons.push_back(std::move(resolutionButton)); // std::move обязателен для передачи умного указателя в вектор
}

void Settings::handleEvent(const sf::Event &event)
{
    for (auto &button : buttons)// передача события каждой кнопке для его обработки
    {
        if(settingsActive){//чтобы кнопки перестали обрабатываться, если меню настроек не является текущим экраном
            button->handleEvent(event);
        }
        else{
            break;
        }
    }
}

void Settings::update(){}

void Settings::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform(); // учет трансформаций экрана при отрисовке всех ее элементов

    for (auto &button : buttons) // отрисовка всех кнопок
        target.draw(*button, states);
}
bool Settings::isSettingsActive()
{
    return settingsActive;
}
void Settings::setSettingsActive(bool active)
{
    Settings::settingsActive = active;
}

//для того, чтобы поменять currentScreen класса Application,
//в классе menu надо как то передать объект класса Application в конструктор класса Settings
//либо же сделать Application singleton.
//но все равно остается проблема с тем, что в конструктор Button передается лямбда - выражение, которое
//не использует никаких параметров, то есть его фукнционал крайне зажат.
//Можно сделать класс Button шаблонным.