#include <string>

#include <imgui-SFML.h>
#include <imgui.h>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "Application.h"
#include "Screen/Menu.h"
#include "Screen/Game.h"

Application::Application()
{
    currentScreen = std::make_unique<Game>(); // устанавливаем текущим окном экран меню

    sf::VideoMode displayProperties = sf::VideoMode::getDesktopMode(); // получаем свойства экрана
    sf::Vector2u displaySize = {displayProperties.width, displayProperties.height};

    // масштабируем и центрируем окно
    window.create(sf::VideoMode((unsigned int)(displaySize.x / 1.5), (unsigned int)(displaySize.y / 1.5)), "Game");
    window.setPosition(static_cast<sf::Vector2i>(displaySize) / 2 - static_cast<sf::Vector2i>(window.getSize()) / 2);

    (void)ImGui::SFML::Init(window); // инициализируем ImGui
}

void Application::handleEvents()
{
    sf::Event event;

    while (window.pollEvent(event)) // проходим по всем событиям, произошедшим с предыдущего кадра
    {
        ImGui::SFML::ProcessEvent(window, event);

        if (event.type == sf::Event::Closed)
            window.close();

        currentScreen->handleEvent(event); // передаем события в обработчик текущего экрана
    }
}

void Application::update()
{
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
