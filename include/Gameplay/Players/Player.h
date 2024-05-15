#ifndef PLAYER_H
#define PLAYER_H

#include "Gameplay/Players/BasePlayer.h"

class Player : public BasePlayer
{
  public:
    Player();
    ~Player() = default;

    void handleEvent(const sf::Event &event, const Camera &camera);
};

#endif