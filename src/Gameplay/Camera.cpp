#include <algorithm>
#include <cassert>
#include <iostream>

#include "Gameplay/Camera.h"

Camera::Camera(sf::Vector2f mapSize, float zoom, float minZoom, float maxZoom, float zoomDelta)
    : mapSize(mapSize), zoom(zoom), minZoom(minZoom), maxZoom(maxZoom), zoomDelta(zoomDelta)
{
    // проверка корректности переданных параметров (отключаются в Release-режиме)
    assert(minZoom < maxZoom);
    assert((minZoom <= zoom) && (zoom <= maxZoom));
    assert(zoomDelta > 1);

    reset(sf::FloatRect(sf::Vector2f(0, 0), mapSize / zoom)); // установка отрисовываемой зоны
}

void Camera::zoomIn()
{
    zoom = std::min(zoom * zoomDelta, maxZoom);

    setSize(mapSize / zoom); // установка отрисовываемой зоны
    // в данном случае проверки не нужны, т. к. при приближении камеры она никогда не выйдет за края игрового поля
}

void Camera::zoomOut()
{
    zoom = std::max(zoom / zoomDelta, minZoom);

    sf::Vector2f newSize = mapSize / zoom;

    sf::FloatRect cameraRectangle(getCenter() - newSize / 2.f, newSize);

    if (cameraRectangle.left < 0) // новая камера выходит за левый край
        cameraRectangle.left = 0;
    if (cameraRectangle.top < 0) // новая камера выходит за верхний край
        cameraRectangle.top = 0;

    if (cameraRectangle.left + cameraRectangle.width > mapSize.x) // новая камера выходит за правый край
        cameraRectangle.left = mapSize.x - cameraRectangle.width;
    if (cameraRectangle.top + cameraRectangle.height > mapSize.y) // новая камера выходит за нижний край
        cameraRectangle.top = mapSize.y - cameraRectangle.height;

    reset(cameraRectangle);
}

void Camera::handleEvent(const sf::Event &event) // обработка событий камеры
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Key::Dash: // нажатие клавиши "-"
            zoomOut();
            break;
        case sf::Keyboard::Key::Equal: // нажатие клавиши "+"
            zoomIn();
            break;
        default:
            break;
        }
    }
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
        if (((offset.x > 0) and (center.x + (size.x / 2) + offset.x <= mapSize.x)) or
            ((offset.x < 0) and (center.x - (size.x / 2) + offset.x >= 0)))
            center.x += offset.x;
        if (((offset.y > 0) and (center.y + (size.y / 2) + offset.y <= mapSize.y)) or
            ((offset.y < 0) and (center.y - (size.y / 2) + offset.y >= 0)))
            center.y += offset.y;
        setCenter(center);
    }
}