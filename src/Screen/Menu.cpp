#include <iostream>

#include <imgui-SFML.h>
#include <imgui.h>

#include "Assets.h"
#include "Screen/Menu.h"
#include "UI/Button.h"
#include "Application.h"
#include "Screen/Settings.h"

bool Menu::menuActive = false;

Menu::Menu()
{
    menuActive = true;
    std::unique_ptr<Button> startButton = std::make_unique<Button>(
        sf::Vector2f(200, 50), "Start", Assets::getInstance().font, 30, [] { std::cout << "Button was pressed\n"; });
    startButton->setBackgroundColor(sf::Color(160, 160, 160), sf::Color(50, 50, 50), sf::Color(90, 90, 90));
    startButton->setTextColor(sf::Color(255, 255, 255));

    std::unique_ptr<Button> settingsButton = std::make_unique<Button>(
        sf::Vector2f(0, 50), sf::Vector2f(200, 50), "Settings", Assets::getInstance().font, 30, []()
        {
            auto s = new Settings();
            Application::getInstance().setCurrentScreen(s);
            Menu::setMenuActive(false);
        });
    settingsButton->setBackgroundColor(sf::Color(160, 160, 160), sf::Color(50, 50, 50), sf::Color(90, 90, 90));
    settingsButton->setTextColor(sf::Color(255, 255, 255));

    buttons.push_back(std::move(settingsButton));
    buttons.push_back(std::move(startButton)); // std::move обязателен для передачи умного указателя в вектор
}

void Menu::handleEvent(const sf::Event &event)
{
    for (auto &button : buttons){
        if(menuActive)//чтобы кнопки перестали обрабатываться, если главное меню не является текущим экраном
        {
            button->handleEvent(event);
        }
        else{
            break;
        }
    } // передача события каждой кнопке для его обработки
}

void Menu::update()
{
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform(); // учет трансформаций экрана при отрисовке всех ее элементов 

    for (auto &button : buttons) // отрисовка всех кнопок
        target.draw(*button, states);
}
bool Menu::isMenuActive()
{
    return menuActive;
}
void Menu::setMenuActive(bool active)
{
    menuActive = active;
}
