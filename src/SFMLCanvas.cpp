/*
 * Author: King Hoe Wong
 * Desc: Implementation for SFMLCanvas class.
 * Courtest of: http://becomingindiedev.blogspot.com/2013/10/qt-5-and-sfml-20-integration.html
 *
 */

#include "SFMLCanvas.h"

#include <iostream>
#include <string>
#include <QDir>

SFMLCanvas::SFMLCanvas(const QPoint &pos, const QSize &size, QWidget *parent)
    : QSFMLWidget(pos, size, parent)
{
}

void SFMLCanvas::onInit()
{
    // Initialize
}

void SFMLCanvas::onUpdate()
{
    // Draw calls should be here
}
