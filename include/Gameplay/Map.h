#ifndef MAP_H
#define MAP_H

#include <array>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Gameplay/Camera.h"
#include "Gameplay/Characters/BaseCharacter.h"
#include "Gameplay/Tiles/BaseTile.h"

#define MAPSIZE 20 // размер игрового поля (ширина и высота)
#define TILE_SIZE_PX 16 // количество пикселей в одной клетке (определяется спрайтами)

class Map : public sf::Drawable, public sf::Transformable
{
  private:
    std::vector<std::unique_ptr<BaseCharacter>> characters; // вектор умных указателей на персонажей
    std::array<std::array<std::shared_ptr<BaseTile>, MAPSIZE>, MAPSIZE>
        tiles; // двумерный массив умных указателей на клетки

    std::unique_ptr<BaseCharacter> *cursor = nullptr; // указатель на выбранного персонажа

  public:
    Map();

    bool isTileFree(sf::Vector2u position) const;

    sf::Vector2u getTileIndex(const sf::Vector2u &point, const Camera &camera) const;

    void handleEvent(const sf::Event &event, const Camera &camera);
    void update();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif