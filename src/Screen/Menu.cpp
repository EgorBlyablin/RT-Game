#include <iostream>

#include "Assets.h"
#include "Screen/Game.h"
#include "Screen/Menu.h"
#include "Screen/Settings.h"
#include "UI/Button.h"

Menu::Menu(sf::Vector2f windowSize, std::function<void(std::unique_ptr<BaseScreen>)> setScreen,
           sf::RenderWindow &window)
    : BaseScreen(windowSize, setScreen)
{
    std::unique_ptr<Button> startButton = std::make_unique<Button>(
        sf::Vector2f(windowSize.x * 0.425, windowSize.y * 0.1), sf::Vector2f(windowSize.x * 0.15, windowSize.y * 0.1),
        "Play", Assets::getInstance().font, 30 * windowSize.y / 800, [windowSize, setScreen] {
            setScreen(
                std::make_unique<Game>(windowSize, [windowSize, setScreen](std::unique_ptr<BaseScreen> newScreen) {
                    setScreen(std::move(newScreen));
                }));
        });
    startButton->setBackgroundColor(sf::Color(160, 160, 160), sf::Color(50, 50, 50), sf::Color(90, 90, 90));
    startButton->setTextColor(sf::Color(255, 255, 255));

    std::unique_ptr<Button> settingsButton = std::make_unique<Button>(
        sf::Vector2f(windowSize.x * 0.425, windowSize.y * 0.2), sf::Vector2f(windowSize.x * 0.15, windowSize.y * 0.1),
        "Settings", Assets::getInstance().font, 30 * windowSize.y / 800, [windowSize, setScreen, &window] {
            setScreen(std::make_unique<Settings>(
                windowSize,
                [windowSize, setScreen](std::unique_ptr<BaseScreen> newScreen) { setScreen(std::move(newScreen)); },
                window));
        });
    settingsButton->setBackgroundColor(sf::Color(160, 160, 160), sf::Color(50, 50, 50), sf::Color(90, 90, 90));
    settingsButton->setTextColor(sf::Color(255, 255, 255));

    buttons.push_back(std::move(startButton)); // std::move обязателен для передачи умного указателя в вектор
    buttons.push_back(std::move(settingsButton));
}

void Menu::handleEvent(const sf::Event &event) // передача события каждой кнопке для его обработки
{
    if (isActive)
        for (auto &button : buttons)
            button->handleEvent(event);
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
