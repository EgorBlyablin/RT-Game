#include <sstream>

#include <SFML/Graphics.hpp>

#include "DebugInfo.h"

#define DEBUG_TEXT_FONT_SIZE 20

FPS::FPS()
{
    clock = sf::Clock();
    clock.restart();
}

int FPS::get()
{
    int result = 1000000 / (clock.getElapsedTime().asMicroseconds() + 1);

    clock.restart();
    return result;
}

DebugInfo::DebugInfo(sf::RenderWindow *window)
{
    this->window = window;

    font = sf::Font();
    font.loadFromFile("Fonts/Arial.ttf");

    fps = FPS();
}

void DebugInfo::draw()
{
    std::stringstream debugText;
    debugText << fps.get() << "fps";

    sf::Text text(debugText.str(), font, DEBUG_TEXT_FONT_SIZE);

    window->draw(text);
}