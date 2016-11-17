/*
 * Author: King Hoe Wong
 * Desc: Implementation for SFMLCanvas class.
 * Courtesy of: http://becomingindiedev.blogspot.com/2013/10/qt-5-and-sfml-20-integration.html
 *
 */

#include "SFMLCanvas.h"

#include <SFML/Graphics.hpp>

#include "State.h"
#include "ResourceIdentifiers.h"
#include "ResourceManager.h"

SFMLCanvas::SFMLCanvas(const QPoint &pos, const QSize &size, State::Context &context, QWidget *parent)
    : QSFMLWidget(pos, size, context, parent)
{
}

void SFMLCanvas::onInit()
{
    // Load texture and initialize sprite with texture.
    getContext().textures.load(Textures::ID::Default, "/Textures/default.png");
    getContext().textures.get(Textures::ID::Default).setSmooth(true);

    mSprite.setTexture(getContext().textures.get(Textures::ID::Default));
    mSprite.setPosition(0.f, 0.f);
    mSprite.scale(0.5f, 0.5f);
}

void SFMLCanvas::onDraw()
{
    // Draw sprite
    sf::RenderWindow::draw(mSprite);
}
