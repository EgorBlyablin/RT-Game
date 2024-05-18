#include <algorithm>
#include <functional>
#include <iostream>
#include <math.h>

#include "Gameplay/Map.h"
#include "Gameplay/Tiles/Cliff.h"
#include "Gameplay/Units/Buildings/Base.h"
#include "Gameplay/Units/Characters/BaseCharacter.h"

#define ROUTE_CIRCLES_RADIUS (TILE_SIZE_PX / 2 / 4)

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

sf::IntRect Map::getViewCoordinates(const sf::View &view) const
{
    std::cout << (view.getCenter() + (view.getSize() / 2.f)).x << ' ' << (view.getCenter() + (view.getSize() / 2.f)).y
              << '\n';

    return sf::IntRect(static_cast<sf::Vector2i>(view.getCenter() - (view.getSize() / 2.f)),
                       static_cast<sf::Vector2i>(view.getCenter() + (view.getSize() / 2.f)));
}

sf::Rect<unsigned int> Map::getTilesToDraw(const sf::IntRect &viewCoordinates) const
{
    return sf::Rect<unsigned int>(
        std::max(0, viewCoordinates.left / TILE_SIZE_PX), std::max(0, viewCoordinates.top / TILE_SIZE_PX),
        std::min(MAPSIZE, (int)std::ceil((float)(viewCoordinates.width - viewCoordinates.left) / TILE_SIZE_PX) + 1),
        std::min(MAPSIZE, (int)std::ceil((float)(viewCoordinates.height - viewCoordinates.top) / TILE_SIZE_PX) + 1));
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
                        cursorCharacter->attack(*it, [this](sf::Vector2u tileIndex) { return isTileFree(tileIndex); });
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

void Map::drawTiles(sf::RenderTarget &target, sf::RenderStates states, sf::Rect<unsigned int> tilesToDraw) const
{
    for (unsigned int y = tilesToDraw.top; y < tilesToDraw.top + tilesToDraw.height; y++)
        for (unsigned int x = tilesToDraw.left; x < tilesToDraw.left + tilesToDraw.width; x++)
        {
            if (x > MAPSIZE - 1 or y > MAPSIZE - 1)
                continue;

            auto &tile = tiles[y][x]; // получение ссылки на клетку

            tile->setPosition((float)x * TILE_SIZE_PX, (float)y * TILE_SIZE_PX); // установка позиции отрисовки
            tile->setScale((float)TILE_SIZE_PX / tile->getArea().width,
                           (float)TILE_SIZE_PX / tile->getArea().height); // масштабирование клетки

            target.draw(*tile, states);
        }
}

void Map::drawUnits(sf::RenderTarget &target, sf::RenderStates states, sf::Rect<unsigned int> tilesToDraw) const
{
    for (auto &player : players)
        for (auto &unit : player->getUnits())
        {
            auto position = unit->getPosition();

            if (tilesToDraw.contains(position))
            {
                unit->Transformable::setPosition(
                    static_cast<sf::Vector2f>(position * (unsigned int)TILE_SIZE_PX)); // установка позиции отрисовки
                unit->setScale((float)TILE_SIZE_PX / unit->getArea().width,
                               (float)TILE_SIZE_PX / unit->getArea().height); // масштабирование клетки

                target.draw(*unit, states);
            }
        }
}

void Map::drawRoute(sf::RenderTarget &target, sf::RenderStates states, sf::Rect<unsigned int> tilesToDraw) const
{
    // отрисовка маршрута
    auto character = dynamic_cast<BaseCharacter *>(cursor->get());

    float radius = ROUTE_CIRCLES_RADIUS;

    sf::CircleShape circle(radius);
    circle.setOrigin(sf::Vector2f(radius, radius));
    circle.setFillColor(sf::Color(0, 0, 0, 0));
    circle.setOutlineColor(sf::Color(255, 255, 255));
    circle.setOutlineThickness((float)TILE_SIZE_PX * 0.03);

    if (character->getPath().size() > 0)
        for (auto &tileIndex : character->getPath())
            if (tilesToDraw.contains(tileIndex))
                if (tileIndex != character->getPosition())
                {
                    circle.setPosition(static_cast<sf::Vector2f>(tileIndex * (unsigned int)TILE_SIZE_PX) +
                                       sf::Vector2f(TILE_SIZE_PX * 0.5f, TILE_SIZE_PX * 0.5f));

                    target.draw(circle, states);
                }
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::View camera = target.getView();

    sf::IntRect viewCoordinates = getViewCoordinates(camera); // положение камеры в игровом мире
    sf::Rect<unsigned int> tilesToDraw = getTilesToDraw(
        viewCoordinates); // крайние клетки для отрисовки (оптимизация, чтобы отрисовывать только видимые клетки)

    drawTiles(target, states, tilesToDraw);
    drawUnits(target, states, tilesToDraw);

    if (cursor != nullptr and dynamic_cast<BaseCharacter *>(cursor->get()) != nullptr)
        drawRoute(target, states, tilesToDraw);
}
