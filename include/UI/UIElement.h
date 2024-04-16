#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

class UIElement : public sf::Drawable, public sf::Transformable
{
public:
    UIElement(float x, float y) { setPosition(x, y); }
    UIElement() : UIElement(0., 0.) {}
};

#endif