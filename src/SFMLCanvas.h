/*
 * Author: King Hoe Wong
 * Desc: Represents an SFMLCanvas. SFML Sprites can be drawn on the canvas.
 * Courtesy of: http://becomingindiedev.blogspot.com/2013/10/qt-5-and-sfml-20-integration.html
 *
 */

#ifndef SFMLCANVAS_H
#define SFMLCANVAS_H

#include <SFML/Graphics.hpp>

#include "QSFMLWidget.h"
#include "State.h"

class SFMLCanvas : public QSFMLWidget
{
public :
    explicit        SFMLCanvas(const QPoint &pos, const QSize &size, State::Context &context, QWidget *parent = 0);

    virtual void    onInit();
    virtual void    onDraw();

private:
    sf::Sprite      mSprite;
};

#endif // SFMLCANVAS_H
