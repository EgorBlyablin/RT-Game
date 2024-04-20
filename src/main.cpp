#include <iostream>

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "RTetris");
    ImGui::SFML::Init(window);

    sf::Clock deltaClock;
    while (window.isOpen()) // цикл отрисовки
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::ShowMetricsWindow();
        ImGui::ShowDebugLogWindow();

        window.clear(); // очистка кадра
        ImGui::SFML::Render(window);
        window.display(); // показ кадра
    }

    return 0;
}