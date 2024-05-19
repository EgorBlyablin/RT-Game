#ifndef CLIFF_H
#define CLIFF_H

#include <SFML/Graphics.hpp>

#include "Assets.h"
#include "Gameplay/Tiles/BaseTile.h"

/// @brief Класс земли
class Cliff : public BaseTile
{
  public:
    Cliff() : BaseTile(Assets::getInstance().cliffTexture, sf::IntRect(16, 16, 16, 16)){};
};

#endif