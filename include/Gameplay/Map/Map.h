#ifndef MAP_H
#define MAP_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "Tile.h"

/// @brief Класс игрового поля
class Map : public sf::Drawable, public sf::Transformable
{
  private:
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles; // двумерный вектор умных указателей на клетки

  public:
    Map();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override; // отрисовка поля
};

#endif