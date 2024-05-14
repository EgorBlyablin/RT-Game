#ifndef BASE_H
#define BASE_H

#include "Gameplay/Units/Buildings/BaseBuilding.h"

/// @brief База игрока (игра оканчивается при ее уничтожении)
class Base : public BaseBuilding
{
  protected:
    unsigned int hp = 500;

  public:
    Base(sf::Vector2u position);
    ~Base() = default; // требуется для умного указателя

    virtual void moveTo(sf::Vector2u targetPosition,
                        std::function<bool(sf::Vector2u)> isTileFree) override; // перемещение в указанную позицию

    virtual void update() override; // обновление состояний
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override; // отрисовка клетки
};

#endif