#include <string>

#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "Game.h"

void Game::init()
{
    sf::VideoMode displayProperties = sf::VideoMode::getDesktopMode();
    sf::Vector2u displaySize = {displayProperties.width, displayProperties.height};

    window.create(
        sf::VideoMode(
            (unsigned int)(displaySize.x / 1.5),
            (unsigned int)(displaySize.y / 1.5)),
        "Game");
    window.setPosition(static_cast<sf::Vector2i>(displaySize) / 2 - static_cast<sf::Vector2i>(window.getSize()) / 2);

    (void)ImGui::SFML::Init(window);
}

void Game::handleEvents()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(window, event);

        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update()
{
    ImGui::SFML::Update(window, ImGuiClock.restart());
}

void Game::render()
{
    ImGui::Begin("Developer tools");
    ImGui::SetWindowSize(ImVec2(150, 50));
    ImGui::Text("FPS: %d", (int)ImGui::GetIO().Framerate);
    ImGui::End();

    window.clear(); // очистка кадра

    ImGui::SFML::Render(window);

    window.display(); // показ кадра
}

void Game::run()
{
    while (window.isOpen()) // цикл отрисовки
    {
        handleEvents();
        update();
        render();
    }
}
