#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "RTetris");

    while (window.isOpen()) // цикл отрисовки
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(); // очистка кадра

        // отрисовка следующего кадра

        window.display(); // показ кадра
    }

    return 0;
}