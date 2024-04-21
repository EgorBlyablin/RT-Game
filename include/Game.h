#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

class Game
{
private:
    static constexpr float windowSize = 0.7; // начальный размер окна по сравнению с экраном

    static inline sf::RenderWindow window; // окно игры
    static inline sf::Clock ImGuiClock{};  // счетчик для ImGui (требуется внутри ImGui)

public:
    static void init(); // инициализация игры

    static void handleEvents(); // обработка пользовательских команд
    static void update();       // обновление внутриигровых событий (перемещение мобов и т. п.)
    static void render();       // отрисовка кадра

    static void run(); // запуск игры (исполнение всех вышеуказанных команд)
};

#endif