#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

#include "Assets.h"

/// @brief Класс игровой клетки
class BaseTile : public sf::Drawable, public sf::Transformable
{
  private:
    const sf::Texture &texture = Assets::getInstance().defaultTexture; // текстура клетки
    sf::IntRect area = sf::IntRect(0, 0, 128, 128); // область текстуры, которая отрисовывается

  public:
    BaseTile() = default;
    ~BaseTile() = default; // требуется для умного указателя

    virtual sf::IntRect getArea() const; // получение области текстуры - требуется для масштабирования

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override; // отрисовка клетки
};

#endif