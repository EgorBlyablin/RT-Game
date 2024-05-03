#ifndef MAP_H
#define MAP_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "../Characters/BaseCharacter.h"
#include "Tiles/BaseTile.h"


#define TILE_SIZE_PX 16 // количество пикселей в одной клетке (определяется спрайтами)

#define MAPSIZE 500 // размер игрового поля (ширина и высота)
// Большое значение установлено для проверки оптимизированности камеры - при отсутствии оптимизации и таком числе клеток
// число кадров в секунду не превысит единицы. В будущем будет установлено конкретное число, на данный момент это абстракция

/// @brief Класс игрового поля
class Map : public sf::Drawable, public sf::Transformable
{
  private:
    std::shared_ptr<BaseTile> tiles[MAPSIZE][MAPSIZE]; // двумерный вектор умных указателей на клетки
    std::unique_ptr<BaseCharacter> characters[MAPSIZE][MAPSIZE]; // двумерный вектор умных указателей на персонажей

  public:
    Map();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override; // отрисовка поля
};

#endif