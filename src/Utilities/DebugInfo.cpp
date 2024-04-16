#include <string>

#include <SFML/Graphics.hpp>

#include "UI/UIElement.h"
#include "Utilities/DebugInfo.h"
#include "Utilities/FPSCounter.h"

#define DEBUG_TEXT_FONT_SIZE 10

DebugInfo::DebugInfo(float x, float y) : UIElement(x, y), fps(FPS()), font(sf::Font())
{
    font.loadFromFile("assets/Fonts/Arial.ttf");
    text = sf::Text("undefined", font, DEBUG_TEXT_FONT_SIZE);
}

void DebugInfo::update()
{
    text.setString("FPS: " + std::to_string(fps.get()));
}

void DebugInfo::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(text, states);
}