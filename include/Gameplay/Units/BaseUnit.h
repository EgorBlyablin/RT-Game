#ifndef BASE_UNIT_H
#define BASE_UNIT_H

#include <functional>

#include <SFML/Graphics.hpp>

#include "Assets.h"

#define SPRITE_SIZE_PX 16

/// @brief Базовый класс любого юнита (персонажа/строения)
class BaseUnit : public sf::Drawable, public sf::Transformable
{
  protected:
    unsigned int hp;
    sf::Vector2u position; // позиция в клеточном поле

    const sf::Texture &texture = Assets::getInstance().defaultTexture;
    sf::IntRect area = sf::IntRect(0, 0, SPRITE_SIZE_PX, SPRITE_SIZE_PX); // участок текстуры для отрисовки

  public:
    BaseUnit(sf::Vector2u position);
    ~BaseUnit() = default; // требуется для умного указателя

    virtual void moveTo(sf::Vector2u targetPosition,
                        std::function<bool(sf::Vector2u)> isTileFree) = 0; // перемещение в указанную позицию

    sf::Vector2u getPosition() const;
    void setPosition(sf::Vector2u position);

    virtual sf::IntRect getArea() const; // получение области текстуры - требуется для масштабирования

    virtual void update() = 0; // обновление состояний
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0; // отрисовка клетки
};

#endif