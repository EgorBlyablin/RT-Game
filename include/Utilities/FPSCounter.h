#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

#include <SFML/System/Clock.hpp>

class FPS
{
private:
    sf::Clock clock;

public:
    FPS();

    int get();
};

#endif