#include <string>

#include <imgui-SFML.h>
#include <imgui.h>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "Application.h"

Application::Application()
{
    currentScreen = std::make_unique<Menu>(); // устанавливаем текущим окном экран меню

    sf::VideoMode displayProperties = sf::VideoMode::getDesktopMode(); // получаем свойства экрана
    sf::Vector2u displaySize = {displayProperties.width, displayProperties.height};

    // масштабируем и центрируем окно
    window.create(sf::VideoMode((unsigned int)(displaySize.x * windowSize), (unsigned int)(displaySize.y * windowSize)), "Game", sf::Style::Default);

    window.setPosition(static_cast<sf::Vector2i>(displaySize) / 2 - static_cast<sf::Vector2i>(window.getSize()) / 2);

    (void)ImGui::SFML::Init(window); // инициализируем ImGui
}

Application &Application::getInstance()
{
    static Application app;
    return app;
}


void Application::handleEvents()
{
    sf::Event event;

    while (window.pollEvent(event)) // проходим по всем событиям, произошедшим с предыдущего кадра
    {
        ImGui::SFML::ProcessEvent(window, event);

        if (event.type == sf::Event::Closed){
            window.close();
        }if(event.type == sf::Event::Resized){//код ниже делает так, что при любом изменении окна точки нажатия
                                              // на кнопки остаются неизменными (без него прямоугольниксъезжает от своего реального места)
            sf::Vector2f windowSize = sf::Vector2f(event.size.width, event.size.height);
            window.setView(sf::View(sf::Vector2f(windowSize.x / 2.f,
                                         windowSize.y / 2.f), sf::Vector2f(windowSize)));
        }

        currentScreen->handleEvent(event); // передаем события в обработчик текущего экрана
    }
}

void Application::update()
{
    currentScreen->update();
    ImGui::SFML::Update(window, ImGuiClock.restart());
}

void Application::render()
{
    ImGui::Begin("Developer tools");
    ImGui::Text("FPS: %d", (int)ImGui::GetIO().Framerate); // выводим число кадров
    ImGui::End();
    ImGui::EndFrame();

    window.clear(); // очищаем кадр

    window.draw(*currentScreen);
    ImGui::SFML::Render(window);

    window.display(); // показываем кадр
}

void Application::run()
{
    while (window.isOpen()) // цикл отрисовки
    {
        handleEvents();
        update();
        render();
    }
    ImGui::SFML::Shutdown();
}
void Application::setCurrentScreen(BaseScreen* newScreen)//не стал в методе делать смену переменных активности на false и true, потому что они
// статические => не наследуются => так как метод не знает, какой экран мы вырубаем, то он и не сможет выключить тот, который надо
// (проще в кнопках, отвечающих за смену экрана самому писать 1 лишнюю строчку, таких кнопок всего 3)
{
    this->currentScreen.reset(newScreen);
    this->currentScreen->update();//без этого все кнопки белые, пока мышкой не двигаешь
}
void Application::setWindow(sf::VideoMode mode)
{
    window.create(mode, "Game", sf::Style::Default);//изменение разрешения
    window.setView(sf::View());//масштабирование объектов на экране
}
const sf::RenderWindow &Application::getWindow() const
{
    return window;
}
