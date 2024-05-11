#include <iostream>

#include "Gameplay/Tiles/Cliff.h"
#include "Screen/Game.h"

Game::Game(sf::Vector2f windowSize)
    : camera(sf::Vector2f(MAPSIZE * TILE_SIZE_PX, MAPSIZE * TILE_SIZE_PX), 1.f, 1.f, 10.f, 1.1f, windowSize)
{
}

void Game::handleEvent(const sf::Event &event) // обработка событий игры
{
    camera.handleEvent(event);
    map.handleEvent(event, camera);
}

void Game::update() // обновление состояний игры
{
    camera.update();
    map.update();
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.setView(camera); // камеру необходимо устанавливать при отрисовке каждого кадра
    map.draw(target, states);
}