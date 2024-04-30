#ifndef MAP_H
#define MAP_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "../Characters/BaseCharacter.h"
#include "Tile.h"

#define MAPSIZE 20 // размер игрового поля (ширина и высота)

/// @brief Класс игрового поля
class Map : public sf::Drawable, public sf::Transformable
{
  private:
    std::shared_ptr<Tile> tiles[MAPSIZE][MAPSIZE]; // двумерный вектор умных указателей на клетки
    std::unique_ptr<BaseCharacter> characters[MAPSIZE][MAPSIZE]; // двумерный вектор умных указателей на персонажей

  public:
    Map();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override; // отрисовка поля
};

#endif