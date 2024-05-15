#include <algorithm>
#include <functional>
#include <iostream>
#include <typeinfo>

#include "Gameplay/Map.h"
#include "Gameplay/Tiles/Cliff.h"
#include "Gameplay/Units/Buildings/Base.h"
#include "Gameplay/Units/Characters/BaseCharacter.h"

Map::Map() : player(), bot()
{
    std::shared_ptr<BaseTile> cliff = std::make_shared<Cliff>(), tile = std::make_shared<BaseTile>();

    for (int i = 0; i < MAPSIZE; i++)
        for (int j = 0; j < MAPSIZE; j++)
            if ((i + j) % 2)
                tiles[i][j] = cliff;
            else
                tiles[i][j] = tile;

    players = {static_cast<BasePlayer *>(&player), static_cast<BasePlayer *>(&bot)};
}

bool Map::isTileFree(sf::Vector2u position) const // проверка клетки на пустоту
{
    if (position.x >= MAPSIZE or position.y >= MAPSIZE)
        return false;

    for (auto &player : players)
        if (std::any_of(player->getUnits().cbegin(), player->getUnits().cend(),
                        [&position](auto &unit) { return position == unit->getPosition(); }))
            return false;
    return true;
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

        if (event.mouseButton.button == sf::Mouse::Button::Left)
        {
            auto it = std::find_if(player.getUnits().begin(), player.getUnits().end(),
                                   [&tileIndex](auto &unit) { return tileIndex == unit->getPosition(); });

            if (it != player.getUnits().end())
                cursor = &(*it);
            else
                cursor = nullptr;
        }

        if (event.mouseButton.button == sf::Mouse::Button::Right) // команда выбранному существу
            if (cursor != nullptr and dynamic_cast<BaseCharacter *>(cursor->get()) != nullptr)
            // если курсор установлен и ссылается на персонажа
            {
                auto cursorCharacter = dynamic_cast<BaseCharacter *>(cursor->get());

                if (isTileFree(tileIndex))
                    cursorCharacter->moveTo(tileIndex,
                                            [this](sf::Vector2u tileIndex) { return isTileFree(tileIndex); });
                else
                {
                    auto it = std::find_if(bot.getUnits().begin(), bot.getUnits().end(),
                                           [&tileIndex](auto &unit) { return tileIndex == unit->getPosition(); });

                    if (it != bot.getUnits().end()) // в указанной клетке присутствует юнит бота
                        cursorCharacter->attack(&(*it),
                                                [this](sf::Vector2u tileIndex) { return isTileFree(tileIndex); });
                }
            }
    }

    player.handleEvent(event, camera);
}

void Map::update()
{
    for (auto &player : players)
        for (auto unitIterator = player->getUnits().begin(); unitIterator != player->getUnits().end();)
        {
            if (unitIterator->get()->getHP() > 0)
            {
                unitIterator->get()->update();
                unitIterator++;
            }
            else
                unitIterator = player->getUnits().erase(unitIterator);
        }
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

    for (auto &player : players)
        for (auto &unit : player->getUnits())
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
