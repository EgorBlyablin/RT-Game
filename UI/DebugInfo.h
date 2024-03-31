#ifndef DEBUG_INFO_H
#define DEBUG_INFO_H

#include <SFML/Graphics.hpp>

class FPS
{
private:
    sf::Clock clock;

public:
    FPS();

    int get();
};

class DebugInfo
{
private:
    sf::RenderWindow *window;

    FPS fps;

    sf::Font font;
    sf::Text text;

public:
    explicit DebugInfo(sf::RenderWindow *window);

    void draw();
};

#endif