#include <algorithm>
#include <cmath>
#include <iostream>

#include "Assets.h"
#include "Gameplay/Map/Map.h"
#include "Gameplay/Map/Tile.h"
#include "Gameplay/Map/Tiles/Cliff.h"

#define TILE_SIZE_PX 16 // количество пикселей в одной клетке (определяется спрайтами)

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

    auto &camera = target.getView(); // получение игровой камеры

    sf::IntRect cameraViewCoordinates(
        (int)((camera.getCenter() - (camera.getSize() / 2.f)).x),
        (int)((camera.getCenter() - (camera.getSize() / 2.f)).y),
        (int)((camera.getCenter() + (camera.getSize() / 2.f)).x),
        (int)((camera.getCenter() + (camera.getSize() / 2.f)).y)); // положение камеры в игровом мире

    int leftTileToDraw = std::max(0, cameraViewCoordinates.left / TILE_SIZE_PX),
        topTileToDraw = std::max(0, cameraViewCoordinates.top / TILE_SIZE_PX),
        rightTileToDraw = std::min(MAPSIZE, cameraViewCoordinates.width / TILE_SIZE_PX + 1),
        bottomTileToDraw = std::min(MAPSIZE, cameraViewCoordinates.height / TILE_SIZE_PX + 1); // крайние клетки для отрисовки (оптимизация, чтобы отрисовывать только видимые клетки)

    for (int i = leftTileToDraw; i < rightTileToDraw; i++)
        for (int j = topTileToDraw; j < bottomTileToDraw; j++)
        {
            auto &tile = tiles[i][j]; // получение ссылки на клетку

            tile->setPosition((float)i * TILE_SIZE_PX, (float)j * TILE_SIZE_PX); // установка позиции отрисовки
            tile->setScale((float)TILE_SIZE_PX / tile->getArea().width,
                           (float)TILE_SIZE_PX / tile->getArea().height); // масштабирование клетки

            target.draw(*tile, states);
        }

    for (int i = leftTileToDraw; i < rightTileToDraw; i++)
        for (int j = topTileToDraw; j < bottomTileToDraw; j++)
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