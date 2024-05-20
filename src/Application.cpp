#include <iostream>
#include <string>

#include <imgui-SFML.h>
#include <imgui.h>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "Application.h"
#include "Screen/Game.h"
#include "Screen/Menu.h"

Application::Application()
{
    sf::VideoMode displayProperties = sf::VideoMode::getDesktopMode(); // получаем свойства экрана
    sf::Vector2u displaySize = {displayProperties.width, displayProperties.height};

    // масштабируем и центрируем окно
    window.create(
        sf::VideoMode((unsigned int)(displaySize.x * windowRatioSize), (unsigned int)(displaySize.y * windowRatioSize)),
        "Game", sf::Style::Default);

    window.setPosition(static_cast<sf::Vector2i>(displaySize) / 2 - static_cast<sf::Vector2i>(window.getSize()) / 2);

    (void)ImGui::SFML::Init(window); // инициализируем ImGui

    setScreen(std::make_unique<Menu>(
        static_cast<sf::Vector2f>(window.getSize()),
        [this](std::unique_ptr<BaseScreen> newScreen) { setScreen(std::move(newScreen)); }, this->window));
}

void Application::setScreen(std::unique_ptr<BaseScreen> newScreen)
{
    nextScreen = std::move(newScreen);
}

void Application::handleEvents()
{
    sf::Event event;

    while (window.pollEvent(event)) // проходим по всем событиям, произошедшим с предыдущего кадра
    {
        ImGui::SFML::ProcessEvent(window, event);

        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        if (event.type == sf::Event::Resized)
        { // код ниже делает так, что при любом изменении окна точки нажатия
          //  на кнопки остаются неизменными (без него прямоугольниксъезжает от своего реального места)
            sf::Vector2f windowSize = sf::Vector2f(event.size.width, event.size.height);
            window.setView(sf::View(sf::Vector2f(windowSize.x / 2.f, windowSize.y / 2.f), sf::Vector2f(windowSize)));
        }

        if (currentScreen != nullptr)
            currentScreen->handleEvent(event); // передаем события в обработчик текущего экрана
    }
}

void Application::update()
{
    if (nextScreen != nullptr)
    {
        if (currentScreen != nullptr)
            currentScreen->setIsActive(false);

        currentScreen = std::move(nextScreen);
        currentScreen->setIsActive(true);
    }

    if (currentScreen != nullptr)
        currentScreen->update();
    ImGui::SFML::Update(window, ImGuiClock.restart());
}

void Application::render()
{
    ImGui::Begin("Developer tools");
    ImGui::Text("FPS: %d", (int)ImGui::GetIO().Framerate); // выводим число кадров
    ImGui::End();
    ImGui::EndFrame();

    window.clear(); // очищаем кадр

    if (currentScreen != nullptr)
        window.draw(*currentScreen);

    ImGui::SFML::Render(window);

    window.display(); // показываем кадр
}

void Application::run()
{
    while (window.isOpen()) // цикл отрисовки
    {
        handleEvents();
        update();
        render();
    }

    ImGui::SFML::Shutdown();
}
