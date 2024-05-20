#include "Application.h"
#include "Assets.h"

int main()
{
    Assets::getInstance().Load(); // Загружаем ресурсы
    Application::getInstance().run();  // Запускаем приложение
    return 0;
}