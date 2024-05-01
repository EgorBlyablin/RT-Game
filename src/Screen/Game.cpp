#include "Screen/Game.h"

Game::Game() : map()
{
    camera.reset(sf::FloatRect(0, 0, 160, 100)); // установка отрисовываемой зоны
    camera.setViewport(sf::FloatRect(0, 0, 1, 1)); // установка размера камеры - весь экран приложения
}

void Game::handleEvent(const sf::Event &event) // обработка событий игры
{
}

void Game::update() // обновление состояний игры
{
    // перемещение камеры (зависит от FPS, необходимо исправить)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        camera.move(0, -1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        camera.move(-1, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        camera.move(0, 1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        camera.move(1, 0);
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.setView(camera); // камеру необходимо устанавливать при отрисовке каждого кадра
    target.draw(map, states);
}