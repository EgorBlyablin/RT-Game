#include <string>

#include <SFML/Graphics.hpp>

#include "DebugInfo.h"

#define DEBUG_TEXT_FONT_SIZE 20

FPS::FPS() : clock(sf::Clock())
{
    clock.restart();
}

int FPS::get()
{
    int result = 1000000 / (clock.getElapsedTime().asMicroseconds() + 1);

    clock.restart();
    return result;
}

DebugInfo::DebugInfo(sf::RenderWindow *window) : font(sf::Font()), fps(FPS())
{
    this->window = window;
    font.loadFromFile("./assets/Fonts/Arial.ttf");

    text = sf::Text("", font, DEBUG_TEXT_FONT_SIZE);
}

void DebugInfo::draw()
{
    text.setString(std::to_string(fps.get()));
    window->draw(text);
}