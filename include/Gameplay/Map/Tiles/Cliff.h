#ifndef CLIFF_H
#define CLIFF_H

#include <SFML/Graphics.hpp>

#include "Assets.h"
#include "BaseTile.h"

/// @brief Класс земли
class Cliff : public BaseTile
{
  private:
    const sf::Texture &texture = Assets::getInstance().cliffTexture;
    sf::IntRect area = sf::IntRect(16, 16, 16, 16);

  public:
    Cliff() = default;

    sf::IntRect getArea() const override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif