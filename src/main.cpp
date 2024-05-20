#include "Application.h"
#include "Assets.h"

int main()
{
    Assets::getInstance().Load(); // Загружаем ресурсы

    Application app;
    app.run(); // Запускаем приложение

    return 0;
}