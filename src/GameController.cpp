//
// Created by Иван on 22.04.2024.
//

#include "GameController.h"

void GameController::Run()
{
    sf::Event event;

    while (m_render->window().isOpen())
    {
        while (m_render->window().pollEvent(event))
        {
            if (event.type == sf::Event::Closed) m_render->window().close();
            if (event.type == sf::Event::KeyPressed)
            {
                // Получаем нажатую клавишу - выполняем соответствующее действие
                if (event.key.code == sf::Keyboard::Escape) m_render->window().close();
                // Новая игра
                if (event.key.code == sf::Keyboard::F2)
                {
                    m_game->Init();
                }
            }
        }

        // Выполняем необходимые действия по отрисовке
        m_render->Render();
    }
}

GameController::~GameController() {
    delete m_game;
    delete m_render;
}

GameController::GameController(GameModel *game, GameRender *render) :m_game(game), m_render(render){}
