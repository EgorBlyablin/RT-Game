#include "Gameplay/Camera.h"

Camera::Camera(int maxWidth, int maxHeight)
{
    setViewport(sf::FloatRect(0, 0, 1, 1)); // установка размера камеры - весь экран приложения
    reset(sf::FloatRect(0, 0, maxWidth, maxHeight)); // установка отрисовываемой зоны
}

void Camera::handleEvent(const sf::Event &event) // обработка событий камеры
{
}

void Camera::update() // обновление состояний игры
{
    // перемещение камеры (зависит от FPS, необходимо исправить)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        move(0, -1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        move(-1, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        move(0, 1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        move(1, 0);
}