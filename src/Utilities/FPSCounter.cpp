#include <SFML/System/Clock.hpp>

#include "Utilities/FPSCounter.h"

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