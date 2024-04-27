#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include "Screen/BaseScreen.h"
#include "Screen/Menu.h"

/// @brief Класс приложения
class Application
{
  private:
    static constexpr float windowSize = 0.7; // начальный размер окна по сравнению с экраном

    sf::RenderWindow window; // окно игры
    std::unique_ptr<BaseScreen> currentScreen;

    static inline sf::Clock ImGuiClock{}; // счетчик для ImGui (требуется внутри ImGui)

    Application(); // инициализация игры

  public:
    static Application& getInstance();

    void handleEvents(); // обработка пользовательских команд
    void update(); // обновление внутриигровых событий (перемещение мобов и т. п.)
    void render(); // отрисовка кадра

    void run(); // запуск игры (исполнение всех вышеуказанных команд)

    void setCurrentScreen(std::unique_ptr<BaseScreen> &currentScreen);
};

#endif