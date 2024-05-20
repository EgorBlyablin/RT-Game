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

bool Settings::settingsActive = false;

Settings::Settings()
{

    sf::VideoMode displayProperties = sf::VideoMode::getDesktopMode(); // получаем свойства экрана
    sf::Vector2f windowSize = {static_cast<float>(displayProperties.width*0.7), static_cast<float>(displayProperties.height*0.7)};//использую это, чтобы распологать кнопки в зависимости от разрешения

    settingsActive = true;

    std::unique_ptr<TurnOnOffButton> turnOnOffButton = std::make_unique<TurnOnOffButton>(
        sf::Vector2f(windowSize.x*0.425, windowSize.y*0.1), sf::Vector2f(windowSize.x*0.15, windowSize.y*0.1), Assets::getInstance().font, 30*windowSize.y/800,
        std::pair<std::function<void(void)>, std::function<void(void)>>{
            []{std::cout<<"on\n";}, []{std::cout<<"off\n";}
        },
        true
        );
    turnOnOffButton->setBackgroundColor(sf::Color(160, 160, 160), sf::Color(50, 50, 50), sf::Color(90, 90, 90));
    turnOnOffButton->setTextColor(sf::Color(255, 255, 255));

    std::unique_ptr<Button> exitButton = std::make_unique<Button>(
        sf::Vector2f(windowSize.x*0.425, windowSize.y*0.2), sf::Vector2f(windowSize.x*0.15, windowSize.y*0.1), "exit", Assets::getInstance().font, 30*windowSize.y/800,
        []
        {
            auto s = new Menu();
            Application::getInstance().setCurrentScreen(s);
            settingsActive = false;
        });
    exitButton->setBackgroundColor(sf::Color(160, 160, 160), sf::Color(50, 50, 50), sf::Color(90, 90, 90));
    exitButton->setTextColor(sf::Color(255, 255, 255));

    std::map<std::string, std::function<void(void )>> callBacks{
        {"640x350", []{
             Application::getInstance().setWindow(sf::VideoMode(640, 350));
         }},
        {"880x600", []{
             Application::getInstance().setWindow(sf::VideoMode(880, 600));
         }},
        {"1024x768", []{
             Application::getInstance().setWindow(sf::VideoMode(1024, 768));
         }}
    };
    std::unique_ptr<SwitchButton> resolutionButton = std::make_unique<SwitchButton>(
        sf::Vector2f(windowSize.x*0.425, windowSize.y*0.3), sf::Vector2f(windowSize.x*0.15, windowSize.y*0.1), "resolution", Assets::getInstance().font, 30*windowSize.y/800,callBacks);

    resolutionButton->setBackgroundColor(sf::Color(160, 160, 160), sf::Color(50, 50, 50), sf::Color(90, 90, 90));
    resolutionButton->setTextColor(sf::Color(255, 255, 255));

    std::unique_ptr<Button> applyButton = std::make_unique<Button>(
        sf::Vector2f(windowSize.x*0.7, windowSize.y*0.1), sf::Vector2f(windowSize.x*0.15, windowSize.y*0.1), "apply", Assets::getInstance().font, 30*windowSize.y/800,[this]
        {
            this->apply();
        });
    exitButton->setBackgroundColor(sf::Color(160, 160, 160), sf::Color(50, 50, 50), sf::Color(90, 90, 90));
    exitButton->setTextColor(sf::Color(255, 255, 255));

    buttons.push_back(std::move(exitButton));
    buttons.push_back(std::move(resolutionButton));
    buttons.push_back(std::move(applyButton));
    buttons.push_back(std::move(turnOnOffButton));
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

void Settings::update(){
    for (auto &button: buttons)
    {
        button->updateColor();
    }
}

void Settings::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform(); // учет трансформаций экрана при отрисовке всех ее элементов

    for (auto &button : buttons) // отрисовка всех кнопок
    {
        target.draw(*button, states);
    }
}
bool Settings::isSettingsActive()
{
    return settingsActive;
}
void Settings::setSettingsActive(bool active)
{
    Settings::settingsActive = active;
}
void Settings::apply()
{
    for (auto &button:buttons)
    {
        button->apply();
    }
}
