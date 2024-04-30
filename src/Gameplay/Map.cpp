#include <iostream>

#include "Assets.h"
#include "Gameplay/Map/Map.h"
#include "Gameplay/Map/Tile.h"
#include "Gameplay/Map/Tiles/Cliff.h"

#define MAPSIZE 20      // размер игрового поля (ширина и высота)
#define TILE_SIZE_PX 50 // отображаемый размер клетки на экране (в будущем будет контролироваться камерой)

Map::Map()
{
    for (int i = 0; i < MAPSIZE; i++)
    {
        tiles.push_back(std::vector<std::unique_ptr<Tile>>());

        for (int j = 0; j < MAPSIZE; j++)
        {
            auto tile = (i + j) % 2 ? std::make_unique<Cliff>() : std::make_unique<Tile>();
            tiles[i].push_back(std::move(tile));
        }
    }
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for (int i = 0; i < (int)tiles.size(); i++)
        for (int j = 0; j < (int)tiles[i].size(); j++)
        {
            auto &tile = tiles[i][j]; // получение ссылки на клетку

            tile->setPosition((float)i * TILE_SIZE_PX, (float)j * TILE_SIZE_PX); // установка позиции отрисовки
            tile->setScale((float)TILE_SIZE_PX / tile->getArea().width,
                           (float)TILE_SIZE_PX / tile->getArea().height); // масштабирование клетки

            target.draw(*tile, states);
        }
}