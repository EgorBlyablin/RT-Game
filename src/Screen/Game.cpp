#include <iostream>

#include "Gameplay/HUD.h"
#include "Screen/Game.h"

#define HUD_WIDTH_RATIO 0.3f

Game::Game(sf::Vector2f windowSize)
    : map(), camera(sf::Vector2f(MAPSIZE * TILE_SIZE_PX, MAPSIZE * TILE_SIZE_PX), 1.f, 1.f, 10.f, 1.1f,
                    sf::Vector2f(windowSize.x * (1 - HUD_WIDTH_RATIO), windowSize.y)),
      hud(&map, &camera, sf::Vector2f(windowSize.x * HUD_WIDTH_RATIO, windowSize.y))
{
    camera.setViewport(sf::FloatRect(0.f, 0.f, 1 - HUD_WIDTH_RATIO, 1.f));

    hud.setPosition(windowSize.x * (1 - HUD_WIDTH_RATIO), 0);
}

void Game::handleEvent(const sf::Event &event) // обработка событий игры
{
    camera.handleEvent(event);
    map.handleEvent(event, camera);
    hud.handleEvent(event, camera);
}

void Game::update() // обновление состояний игры
{
    camera.update();
    map.update();
    hud.update();
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.setView(camera); // камеру необходимо устанавливать при отрисовке каждого кадра
    target.draw(map, states);

    target.setView(target.getDefaultView());
    target.draw(hud, states);
}