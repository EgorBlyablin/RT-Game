#include "Screen/Game.h"

Game::Game() : map()
{
}

void Game::handleEvent(const sf::Event &event) // обработка событий игры
{
}

void Game::update() // обновление состояний игры
{
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(map, states);
}