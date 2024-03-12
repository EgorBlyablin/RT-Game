#include <fstream>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "UI/DebugInfo.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(320, 240), "RTetris");
    DebugInfo debugInfo(&window);

    while (window.isOpen()) // цикл отрисовки
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(); // очистка кадра

        debugInfo.draw();
        // отрисовка следующего кадра

        window.display(); // показ кадра
    }

    return 0;
}