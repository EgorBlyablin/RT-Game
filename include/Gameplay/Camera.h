#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

/// @brief Класс камеры
class Camera : public sf::View
{
  private:
    sf::Vector2f mapSize;
    float zoom, minZoom, maxZoom, zoomDelta;

    sf::Vector2f windowSize;

    void zoomIn();  // увеличение масштаба
    void zoomOut(); // уменьшение масштаба

  public:
    /// @brief Инициализация камеры
    /// @param mapSize размер игрового поля
    /// @param zoom приближение камеры - которая часть всего поля видна пользователю
    /// @param minZoom минимальное приближение камеры
    /// @param maxZoom максимальное приближение камеры
    /// @param windowSize размеры окна приложения
    Camera(sf::Vector2f mapSize, float zoom, float minZoom, float maxZoom, float zoomDelta, sf::Vector2f windowSize);

    sf::Vector2u mapCoordsToPixel(const sf::Vector2u &point) const;

    float getZoom() const;
    sf::Vector2f getWindowSize() const;

    void handleEvent(const sf::Event &event); // обработка событий
    void update();                            // обновление состояния
};

#endif