#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include "Screen/BaseScreen.h"

/// @brief Класс приложения
class Application
{
  private:
    const float windowRatioSize = 0.7; // начальный размер окна по сравнению с экраном

    sf::RenderWindow window; // окно игры
    std::unique_ptr<BaseScreen> currentScreen;
    std::unique_ptr<BaseScreen> nextScreen;

    static inline sf::Clock ImGuiClock{}; // счетчик для ImGui (требуется внутри ImGui)

  public:
    Application(); // инициализация игры

    void setScreen(std::unique_ptr<BaseScreen> newScreen);

    void handleEvents(); // обработка пользовательских команд
    void update(); // обновление внутриигровых событий (перемещение мобов и т. п.)
    void render(); // отрисовка кадра

    void run(); // запуск игры (исполнение всех вышеуказанных команд)
};

#endif