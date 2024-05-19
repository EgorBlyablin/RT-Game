#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>

#include "Gameplay/Camera.h"
#include "Gameplay/Map.h"

class HUD : public sf::Drawable, public sf::Transformable
{
  private:
    Map *map;
    Camera *camera;

    sf::Vector2f size;

  public:
    HUD(Map *map, Camera *camera, sf::Vector2f size);

    void handleEvent(const sf::Event &event, const Camera &camera);
    void update();

    void drawUnitInfo(sf::RenderTarget &target, sf::RenderStates states) const;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif