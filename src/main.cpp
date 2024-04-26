#include "Assets.h"
#include "Game.h"

int main()
{
    Assets::getInstance().Load(); // Загружаем ресурсы
    Game game;                    // Создаем модель игры
    game.run();                   // Запускаем игру

    return 0;
}