#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

/// @brief Класс камеры
class Camera : public sf::View
{
  private:
    int mapWidth, mapHeight;

    float zoom, minZoom, maxZoom;

  public:
    /// @brief Инициализация камеры
    /// @param mapWidth ширина игрового поля
    /// @param mapHeight высота игрового поля
    /// @param minZoom минимальное приближение камеры
    /// @param maxZoom максимальное приближение камеры
    /// @param zoom приближение камеры - которая часть всего поля видна пользователю
    Camera(int mapWidth, int mapHeight, float zoom, float minZoom, float maxZoom);

    void handleEvent(const sf::Event &event); // обработка событий
    void update();                            // обновление состояния
};

#endif