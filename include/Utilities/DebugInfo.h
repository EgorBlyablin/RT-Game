#ifndef DEBUG_INFO_H
#define DEBUG_INFO_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "../UI/UIElement.h"
#include "FPSCounter.h"

class DebugInfo : public UIElement
{
protected:
    FPS fps;

    sf::Font font;
    sf::Text text;

public:
    DebugInfo(float x, float y);
    DebugInfo() : DebugInfo(0, 0) {}

    void update();

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif