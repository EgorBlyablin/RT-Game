#ifndef BOT_H
#define BOT_H

#include "Gameplay/Players/BasePlayer.h"

class Bot : public BasePlayer
{
  public:
    Bot();
    ~Bot() = default;
};

#endif