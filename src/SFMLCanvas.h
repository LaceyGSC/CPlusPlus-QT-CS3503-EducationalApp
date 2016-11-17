/*
 * Author: King Hoe Wong
 * Desc: Represents an SFMLCanvas. Sprites should be drawn on the canvas.
 * Courtest of: http://becomingindiedev.blogspot.com/2013/10/qt-5-and-sfml-20-integration.html
 *
 */

#ifndef SFMLCANVAS_H
#define SFMLCANVAS_H

#include "QSFMLWidget.h"

#include <SFML/Graphics.hpp>

class SFMLCanvas : public QSFMLWidget
{
public :
    explicit SFMLCanvas(const QPoint &pos, const QSize &size, QWidget *parent = 0);

    virtual void onInit();
    virtual void onUpdate();
};

#endif // SFMLCANVAS_H
