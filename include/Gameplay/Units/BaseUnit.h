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
    sf::Vector2u position; // позиция в клеточном поле
    unsigned int hp;       // очки здоровья
    unsigned int maxHP;    // максимальное здоровье персонажа

    const sf::Texture &texture;
    sf::IntRect area; // участок текстуры для отрисовки

  public:
    BaseUnit(sf::Vector2u position, unsigned int hp, unsigned int maxHP,
             const sf::Texture &texture = Assets::getInstance().defaultTexture,
             sf::IntRect area = sf::IntRect(0, 0, SPRITE_SIZE_PX, SPRITE_SIZE_PX));
    ~BaseUnit() = default; // требуется для умного указателя

    sf::Vector2u getPosition() const;
    unsigned int getHP() const;
    unsigned int getMaxHP() const;
    const sf::Texture &getTexture() const;
    sf::IntRect getArea() const; // получение области текстуры - требуется для масштабирования

    void setPosition(sf::Vector2u position);
    void setHP(unsigned int hp);

    virtual void update(); // обновление состояний
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override; // отрисовка клетки

    static unsigned int distance(sf::Vector2u first, sf::Vector2u second);
};

#endif