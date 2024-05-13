#include <algorithm>
#include <functional>
#include <iostream>

#include "Gameplay/Map.h"
#include "Gameplay/Tiles/Cliff.h"
#include "Gameplay/Units/Buildings/Base.h"
#include "Gameplay/Units/Characters/BaseCharacter.h"

Map::Map()
{
    std::shared_ptr<BaseTile> cliff = std::make_shared<Cliff>(), tile = std::make_shared<BaseTile>();

    for (int i = 0; i < MAPSIZE; i++)
        for (int j = 0; j < MAPSIZE; j++)
            if ((i + j) % 2)
                tiles[i][j] = cliff;
            else
                tiles[i][j] = tile;

    auto base = std::make_unique<Base>(sf::Vector2u(0, 0));
    auto character = std::make_unique<BaseCharacter>(sf::Vector2u(1, 1));

    units.push_back(std::move(base));
    units.push_back(std::move(character));
}

bool Map::isTileFree(sf::Vector2u position) const // проверка клетки на пустоту
{
    return std::none_of(units.cbegin(), units.cend(),
                        [&position](auto &unit) { return position == unit->getPosition(); });
}

sf::Vector2u Map::getTileIndex(const sf::Vector2u &point, const Camera &camera) const
// получение индекса клетки по точке с учетом камеры
{
    sf::Vector2u pixelPosition(camera.mapCoordsToPixel(sf::Vector2u(point.x, point.y)));
    sf::Vector2u tileIndex(pixelPosition.x / TILE_SIZE_PX, pixelPosition.y / TILE_SIZE_PX);

    return tileIndex;
}

void Map::handleEvent(const sf::Event &event, const Camera &camera)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2u tileIndex = getTileIndex(sf::Vector2u(event.mouseButton.x, event.mouseButton.y), camera);

        if (cursor == nullptr) // установка курсора
        {
            auto it = std::find_if(units.begin(), units.end(),
                                   [&tileIndex](auto &unit) { return tileIndex == unit->getPosition(); });

            if (it != units.end())
                cursor = &(*it);
        }
        else // команда выбранному существу
        {
            if (isTileFree(tileIndex))
                (*cursor)->moveTo(tileIndex, [this](sf::Vector2u tileIndex) { return isTileFree(tileIndex); });
        }
    }
}

void Map::update()
{
    for (auto &unit : units)
        unit->update();
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::View camera = target.getView();

    sf::IntRect cameraViewCoordinates((int)((camera.getCenter() - (camera.getSize() / 2.f)).x),
                                      (int)((camera.getCenter() - (camera.getSize() / 2.f)).y),
                                      (int)((camera.getCenter() + (camera.getSize() / 2.f)).x),
                                      (int)((camera.getCenter() + (camera.getSize() / 2.f)).y));
    // положение камеры в игровом мире

    unsigned int leftTileToDraw = std::max(0, cameraViewCoordinates.left / TILE_SIZE_PX),
                 topTileToDraw = std::max(0, cameraViewCoordinates.top / TILE_SIZE_PX),
                 rightTileToDraw = std::min(MAPSIZE, cameraViewCoordinates.width / TILE_SIZE_PX + 1),
                 bottomTileToDraw = std::min(MAPSIZE, cameraViewCoordinates.height / TILE_SIZE_PX + 1);
    // крайние клетки для отрисовки (оптимизация, чтобы отрисовывать только видимые клетки)

    for (unsigned int i = leftTileToDraw; i < rightTileToDraw; i++)
        for (unsigned int j = topTileToDraw; j < bottomTileToDraw; j++)
        {
            auto &tile = tiles[i][j]; // получение ссылки на клетку

            tile->setPosition((float)i * TILE_SIZE_PX, (float)j * TILE_SIZE_PX); // установка позиции отрисовки
            tile->setScale((float)TILE_SIZE_PX / tile->getArea().width,
                           (float)TILE_SIZE_PX / tile->getArea().height); // масштабирование клетки

            target.draw(*tile, states);
        }

    for (auto &unit : units)
    {
        auto position = unit->getPosition();

        if (leftTileToDraw <= position.x && position.x <= rightTileToDraw && topTileToDraw <= position.y &&
            position.y <= bottomTileToDraw)
        {
            unit->Transformable::setPosition(
                static_cast<sf::Vector2f>(position * (unsigned int)TILE_SIZE_PX)); // установка позиции отрисовки
            unit->setScale((float)TILE_SIZE_PX / unit->getArea().width,
                           (float)TILE_SIZE_PX / unit->getArea().height); // масштабирование клетки

            target.draw(*unit, states);
        }
    }
}
