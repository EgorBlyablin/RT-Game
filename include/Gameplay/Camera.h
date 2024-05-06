#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

/// @brief Класс камеры
class Camera : public sf::View
{
  private:
    sf::Vector2f mapSize;

    float zoom, minZoom, maxZoom, zoomDelta;

    void zoomIn(); // увеличение масштаба
    void zoomOut(); // уменьшение масштаба

  public:
    /// @brief Инициализация камеры
    /// @param mapSize размер игрового поля
    /// @param zoom приближение камеры - которая часть всего поля видна пользователю
    /// @param minZoom минимальное приближение камеры
    /// @param maxZoom максимальное приближение камеры
    Camera(sf::Vector2f mapSize, float zoom, float minZoom, float maxZoom, float zoomDelta);

    void handleEvent(const sf::Event &event); // обработка событий
    void update();                            // обновление состояния
};

#endif