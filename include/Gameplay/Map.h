#ifndef MAP_H
#define MAP_H

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Gameplay/Camera.h"
#include "Gameplay/Players/Bot.h"
#include "Gameplay/Players/Player.h"
#include "Gameplay/Tiles/BaseTile.h"
#include "Gameplay/Units/BaseUnit.h"

#define MAPSIZE 20 // размер игрового поля (ширина и высота)
#define TILE_SIZE_PX 16 // количество пикселей в одной клетке (определяется спрайтами)

class Map : public sf::Drawable, public sf::Transformable
{
  private:
    std::shared_ptr<BaseTile> tiles[MAPSIZE][MAPSIZE]; // двумерный массив умных указателей на клетки

    std::unique_ptr<BaseUnit> *cursor = nullptr; // указатель на выбранного юнита

    Player player; // игрок
    Bot bot;       // противник

    std::vector<BasePlayer *> players; // вектор указателей на всех игроков (необходимо для итерации по игрокам)

  public:
    Map();

    bool isTileFree(sf::Vector2u position) const;

    sf::Vector2u getTileIndex(const sf::Vector2u &point, const Camera &camera) const;
    sf::IntRect getViewCoordinates(const sf::View &view) const;
    sf::Rect<unsigned int> getTilesToDraw(const sf::IntRect &viewCoordinates) const;

    void handleEvent(const sf::Event &event, const Camera &camera);
    void update();

    void drawTiles(sf::RenderTarget &target, sf::RenderStates states, sf::Rect<unsigned int> tilesToDraw) const;
    void drawUnits(sf::RenderTarget &target, sf::RenderStates states, sf::Rect<unsigned int> tilesToDraw) const;
    void drawRoute(sf::RenderTarget &target, sf::RenderStates states, sf::Rect<unsigned int> tilesToDraw) const;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif