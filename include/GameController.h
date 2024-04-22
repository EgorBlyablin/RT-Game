//
// Created by Иван on 22.04.2024.
//

#ifndef RTETRIS_GAMECONTROLLER_H
#define RTETRIS_GAMECONTROLLER_H


#include <SFML/Graphics.hpp>
#include "GameRender.h"

class GameController
{
    GameModel *m_game;
    GameRender *m_render;
public:
    GameController(GameModel *game, GameRender *render);

    void Run();

    virtual ~GameController();
};


#endif //RTETRIS_GAMECONTROLLER_H
