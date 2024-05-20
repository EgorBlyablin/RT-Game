#include "Screen/BaseScreen.h"

sf::Vector2f BaseScreen::getWindowSize() const
{
    return windowSize;
}

bool BaseScreen::getIsActive() const
{
    return isActive;
}

void BaseScreen::setWindowSize(sf::Vector2f windowSize)
{
    this->windowSize = windowSize;
}

void BaseScreen::setIsActive(bool isActive)
{
    this->isActive = isActive;
}
