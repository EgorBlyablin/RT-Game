#include "Screen/Game.h"

Game::Game() : map(), camera()
{
}

void Game::handleEvent(const sf::Event &event) // обработка событий игры
{
    camera.handleEvent(event);
}

void Game::update() // обновление состояний игры
{
    camera.update();
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.setView(camera); // камеру необходимо устанавливать при отрисовке каждого кадра
    target.draw(map, states);
}