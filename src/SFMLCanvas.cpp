/*
 * Author: King Hoe Wong
 * Desc: Implementation for SFMLCanvas class.
 * Courtesy of: http://becomingindiedev.blogspot.com/2013/10/qt-5-and-sfml-20-integration.html
 *
 */

#include "SFMLCanvas.h"

SFMLCanvas::SFMLCanvas(const QPoint &pos, const QSize &size, QWidget *parent)
    : QSFMLWidget(pos, size, parent)
{
}

void SFMLCanvas::onInit()
{
    // Initialize sprites with textures, etc.
}

void SFMLCanvas::onUpdate()
{
    // SFML draw calls should be here
}
