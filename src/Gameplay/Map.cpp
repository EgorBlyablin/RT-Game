#include <iostream>

#include "Assets.h"
#include "Gameplay/Map/Map.h"
#include "Gameplay/Map/Tile.h"
#include "Gameplay/Map/Tiles/Cliff.h"

#define TILE_SIZE_PX 50 // отображаемый размер клетки на экране (в будущем будет контролироваться камерой)

Map::Map()
{
    std::shared_ptr<Tile> cliff = std::make_shared<Cliff>(), tile = std::make_shared<Tile>();

    for (int i = 0; i < MAPSIZE; i++)
        for (int j = 0; j < MAPSIZE; j++)
            if ((i + j) % 2)
                tiles[i][j] = cliff;
            else
                tiles[i][j] = tile;

    characters[0][0] = std::make_unique<BaseCharacter>();
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for (int i = 0; i < MAPSIZE; i++)
        for (int j = 0; j < MAPSIZE; j++)
        {
            auto &tile = tiles[i][j]; // получение ссылки на клетку

            tile->setPosition((float)i * TILE_SIZE_PX, (float)j * TILE_SIZE_PX); // установка позиции отрисовки
            tile->setScale((float)TILE_SIZE_PX / tile->getArea().width,
                           (float)TILE_SIZE_PX / tile->getArea().height); // масштабирование клетки

            target.draw(*tile, states);
        }

    for (int i = 0; i < MAPSIZE; i++)
        for (int j = 0; j < MAPSIZE; j++)
        {
            auto &character = characters[i][j]; // получение ссылки на клетку

            if (character != nullptr)
            {
                character->setPosition((float)i * TILE_SIZE_PX, (float)j * TILE_SIZE_PX); // установка позиции отрисовки
                character->setScale((float)TILE_SIZE_PX / character->getArea().width,
                                    (float)TILE_SIZE_PX / character->getArea().height); // масштабирование клетки

                target.draw(*character, states);
            }
        }
}