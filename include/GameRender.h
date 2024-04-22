//
// Created by Иван on 22.04.2024.
//

#ifndef RTETRIS_GAMERENDER_H
#define RTETRIS_GAMERENDER_H


#include <SFML/Graphics.hpp>
#include "GameModel.h"

class GameRender : public sf::Drawable, public sf::Transformable
{
    GameModel *m_game;
    sf::RenderWindow m_window;
    sf::Text m_text;
public:
    explicit GameRender(GameModel *game);

    ~GameRender() override;

    sf::RenderWindow& window() { return m_window; };
    bool Init();
    void Render();
public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif //RTETRIS_GAMERENDER_H
