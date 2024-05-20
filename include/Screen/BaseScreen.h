#ifndef BASE_SCREEN_H
#define BASE_SCREEN_H

#include <functional>
#include <vector>

#include <SFML/Graphics.hpp>

#include "UI/Button.h"

/// @brief Абстрактный класс экрана
/// @details Экранами являются все отображаемые окна:
/// начальное меню, настройки, меню паузы и даже сам экран игры.
/// Каждый кадр они обрабатывают события и обновляют свои свойства
class BaseScreen : public sf::Drawable, public sf::Transformable
{
  protected:
    std::vector<std::unique_ptr<Button>> buttons; // все кнопки экрана

    sf::Vector2f windowSize;
    std::function<void(std::unique_ptr<BaseScreen>)> setScreen;

    sf::RenderWindow &window;

    bool isActive = false;

  public:
    BaseScreen(sf::Vector2f windowSize, std::function<void(std::unique_ptr<BaseScreen>)> setScreen,
               sf::RenderWindow &window)
        : windowSize(windowSize), setScreen(setScreen), window(window)
    {
    }

    sf::Vector2f getWindowSize() const;
    bool getIsActive() const;

    void setWindowSize(sf::Vector2f windowSize);
    void setIsActive(bool isActive);

    virtual void handleEvent(const sf::Event &event) = 0; // обработка событий
    virtual void update() = 0;                            // обновление свойств
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0; // отрисовка
};

#endif