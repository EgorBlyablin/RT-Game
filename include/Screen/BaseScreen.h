#ifndef BASE_SCREEN_H
#define BASE_SCREEN_H

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

  public:
    virtual void handleEvent(const sf::Event &event) = 0; // обработка событий
    virtual void update() = 0;                            // обновление свойств
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0; // отрисовка
};

#endif