/*
 * Author: King Hoe Wong
 * Desc: Represents an WorldCanvas. SFML Sprites can be drawn on the canvas.
 * Courtesy of: http://becomingindiedev.blogspot.com/2013/10/qt-5-and-sfml-20-integration.html
 *
 */

#ifndef WorldCanvas_H
#define WorldCanvas_H

#include <SFML/Graphics.hpp>

#include "QSFMLWidget.h"
#include "State.h"

class WorldCanvas : public QSFMLWidget
{
public :
    explicit        WorldCanvas(const QPoint &pos, const QSize &size, State::Context &context, QWidget *parent = 0);

    virtual void    onInit();
    virtual void    onDraw(sf::RenderTarget& target, sf::RenderStates states);

private:
    sf::Sprite      mSprite;
};

#endif // WorldCanvas_H
