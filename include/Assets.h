//
// Created by Иван on 22.04.2024.
//

#ifndef RTETRIS_ASSETS_H
#define RTETRIS_ASSETS_H


#include <SFML/Graphics.hpp>

class Assets {
public:
    sf::Font font;
public:
    static Assets &Instance() {
        static Assets s;
        return s;
    }

    void Load() {
        font.loadFromFile("assets/fonts/Arial.ttf");
    }

private:
    Assets() = default;

    ~Assets() = default;

    Assets(Assets const &) = delete;

    Assets &operator=(Assets const &) = delete;
};

#endif //RTETRIS_ASSETS_H
