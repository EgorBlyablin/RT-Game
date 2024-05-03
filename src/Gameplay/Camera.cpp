#include "Gameplay/Camera.h"

Camera::Camera(int mapWidth, int mapHeight, float zoom, float minZoom, float maxZoom)
    : mapWidth(mapWidth), mapHeight(mapHeight), zoom(zoom), minZoom(minZoom), maxZoom(maxZoom)
{
    reset(sf::FloatRect(0, 0, mapWidth / zoom, mapHeight / zoom)); // установка отрисовываемой зоны
}

void Camera::handleEvent(const sf::Event &event) // обработка событий камеры
{
}

void Camera::update() // обновление состояний игры
{
    sf::Vector2f offset;               // смещение камеры
    sf::Vector2f center = getCenter(), // позиция центра камеры
        size = getSize();              // размеры прямоугольника камеры

    // перемещение камеры (зависит от FPS, необходимо исправить)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        offset.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        offset.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        offset.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        offset.x += 1.f;

    if (offset.x or offset.y) // если задано смещение
    {
        // проверяем, что при смещении прямоугольник камеры не выйдет за края игрового поля
        // проверка положительного и отрицательного смещения проводится для того, чтобы в случае, если камера ошибочно
        // окажется за пределами игрового поля, она смогла вернуться в его пределы
        if (((offset.x > 0) and (center.x + (size.x / 2) + offset.x <= mapWidth)) or
            ((offset.x < 0) and (center.x - (size.x / 2) + offset.x >= 0)))
            center.x += offset.x;
        if (((offset.y > 0) and (center.y + (size.y / 2) + offset.y <= mapHeight)) or
            ((offset.y < 0) and (center.y - (size.y / 2) + offset.y >= 0)))
            center.y += offset.y;
        setCenter(center);
    }
}