#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

/// @brief Класс камеры
class Camera : public sf::View
{
  private:
    sf::Vector2f mapSize;
    float zoom, minZoom, maxZoom, zoomDelta;

    sf::Vector2f viewSize;

    void zoomIn();  // увеличение масштаба
    void zoomOut(); // уменьшение масштаба

  public:
    /// @brief Инициализация камеры
    /// @param mapSize размер игрового поля
    /// @param zoom приближение камеры - которая часть всего поля видна пользователю
    /// @param minZoom минимальное приближение камеры
    /// @param maxZoom максимальное приближение камеры
    /// @param viewSize размеры области камеры на экране
    Camera(sf::Vector2f mapSize, float zoom, float minZoom, float maxZoom, float zoomDelta, sf::Vector2f viewSize);

    sf::Vector2u mapCoordsToPixel(const sf::Vector2u &point) const;

    void handleEvent(const sf::Event &event); // обработка событий
    void update();                            // обновление состояния
};

#endif