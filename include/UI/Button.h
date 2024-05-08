#ifndef BUTTON_H
#define BUTTON_H

#include <functional>

#include <SFML/Graphics.hpp>


/// @brief Класс кнопки
/// @details Выполняет отрисовку кнопки в соответствии с ее состоянием,
/// изменяет ее состояние в соответствии с событиями,
/// вызывает callback-функцию
/// @todo возможно, в последствии потребуется использовать текстуру, вместо отдельной отрисовки фона и текста
class Button : public sf::Drawable, public sf::Transformable
{
  private:
    std::function<void(void)> callback; // функция, вызываемая кнопкой при ее отпускании

    bool isPressed = false; // состояние нажатия
    bool isHovered = false; // состояние наведения

    bool isDisable = false;

  protected:
    sf::Color backgroundColor{127, 127, 127};     // стандартный цвет фона кнопки
    sf::Color backgroundColorOnClick{32, 32, 32}; // цвет при нажатии
    sf::Color backgroundColorOnHover{64, 64, 64}; // цвет при наведении

    sf::Color textColor{255, 255, 255};        // стандартный цвет текста кнопки
    sf::Color textColorOnClick{127, 127, 127}; // цвет при нажатии
    sf::Color textColorOnHover{200, 200, 200}; // цвет при наведении

    sf::RectangleShape shape; // фон кнопки
    sf::Text text;            // текст кнопки

  public:
    Button(){};
    Button(
        const sf::Vector2f &position, const sf::Vector2f &size, const std::string &text, const sf::Font &font,
        const unsigned int characterSize, std::function<void(void)> callback = []() {});
    Button(
        const sf::Vector2f &size, const std::string &text, const sf::Font &font, const unsigned int characterSize,
        std::function<void(void)> callback = []() {})
        : Button(sf::Vector2f(0, 0), size, text, font, characterSize, callback)
    {
    }

    void setBackgroundColor(const sf::Color &color, const sf::Color &onClick,
                            const sf::Color &onHover);                         // установка цвета фона
    void setBackgroundColor(const sf::Color &color, const sf::Color &onClick); // установка цвета фона
    void setBackgroundColor(const sf::Color &color);                           // установка цвета фона

    void setTextColor(const sf::Color &color, const sf::Color &onClick,
                      const sf::Color &onHover);                         // установка цвета текста
    void setTextColor(const sf::Color &color, const sf::Color &onClick); // установка цвета текста
    void setTextColor(const sf::Color &color);                           // установка цвета текста

    virtual void updateColor(); // обновление текущих цветов в соответствии с состоянием

    /// @brief Установка положения кнопки
    /// @param position позиция верхнего левого края кнопки
    virtual void setPosition(sf::Vector2f position);

    void setIsDisable(bool isDisable);

    virtual void handleEvent(const sf::Event &event);                                   // обработка событий
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const; // отрисовка кнопки
};

#endif