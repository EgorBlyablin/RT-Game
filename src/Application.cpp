#include <string>

#include <imgui-SFML.h>
#include <imgui.h>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "Application.h"

Application::Application()
{
    currentScreen = std::make_unique<Menu>(); // устанавливаем текущим окном экран меню

    sf::VideoMode displayProperties = sf::VideoMode::getDesktopMode(); // получаем свойства экрана
    sf::Vector2u displaySize = {displayProperties.width, displayProperties.height};

    // масштабируем и центрируем окно
    window.create(sf::VideoMode((unsigned int)(displaySize.x * windowSize), (unsigned int)(displaySize.y * windowSize)), "Game");
    window.setPosition(static_cast<sf::Vector2i>(displaySize) / 2 - static_cast<sf::Vector2i>(window.getSize()) / 2);

    (void)ImGui::SFML::Init(window); // инициализируем ImGui
}

Application &Application::getInstance()
{
    static Application app;
    return app;
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
void Application::setCurrentScreen(BaseScreen* newScreen)
{
    this->currentScreen.reset(newScreen);
}
void Application::setWindow(sf::VideoMode mode)
{
    window.create(mode, "Game");
}
const sf::RenderWindow &Application::getWindow() const
{
    return window;
}
