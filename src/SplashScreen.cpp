/*
 * Author: King Hoe Wong
 * Desc: Implementation for splash screen.
 *
 */

#include "SplashScreen.h"

SplashScreen::SplashScreen(const QPoint &pos, const QSize &size, State::Context &context, QWidget *parent)
    : QSFMLWidget(pos, size, context, parent)
{
}

void SplashScreen::onInit()
{
}

void SplashScreen::onDraw(sf::RenderTarget& target, sf::RenderStates states)
{
}
