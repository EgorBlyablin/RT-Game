#include "Application.h"
#include "Assets.h"

int main()
{
    Assets::getInstance().Load(); // Загружаем ресурсы
    Application app;              // Создаем модель игры
    app.run();                    // Запускаем приложение

    return 0;
}