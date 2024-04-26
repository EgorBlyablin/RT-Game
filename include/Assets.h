//
// Created by Иван on 22.04.2024.
//

#ifndef RTETRIS_ASSETS_H
#define RTETRIS_ASSETS_H

#include <SFML/Graphics.hpp>

/// @brief Синглтон для работы с ассетами (текстурами, шрифтами, звуками и т.д.)
class Assets
{
  public:
    sf::Font font; // шрифт

  public:
    void Load() // загрузка ассетов
    {
        font.loadFromFile("assets/fonts/Arial.ttf");
    }

    static Assets &getInstance() // получение синглтона
    {
        static Assets s;
        return s;
    }

  private:
    Assets() = default;
    Assets(Assets const &) = delete;
    ~Assets() = default;

    Assets &operator=(Assets const &) = delete;
};

#endif // RTETRIS_ASSETS_H
