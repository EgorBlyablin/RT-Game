#include "Assets.h"
#include "GameModel.h"
#include "GameController.h"
#include "GameRender.h"


int main()
{
    Assets::Instance().Load();			// Загружаем ресурсы
    GameModel game;					// Создаем модель игры
    GameRender render(&game);			// Создаем представление
    GameController controller(&game, &render);	// Создаем контроллер
    controller.Run();				// Запускаем игру
    return 0;
}