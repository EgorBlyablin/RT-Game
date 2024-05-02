#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

/// @brief Класс камеры
class Camera : public sf::View
{
  public:
    /// @brief Инициализация камеры
    /// @param maxWidth ширина области камеры
    /// @param maxHeight высота области камеры
    /// @details Переданные аргументы определяют размеры прямоугольника области видимости игрового поля, которая
    /// впоследствии будет растянута на весь экран
    Camera(int maxWidth, int maxHeight);

    void handleEvent(const sf::Event &event); // обработка событий
    void update();                            // обновление состояния
};

#endif