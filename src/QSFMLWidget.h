/*
 * Author: King Hoe Wong
 * Desc: Abstract class for a Qt + SFML widget. Any widgets that inherit from this class will
 *       allow SFML to draw sprites onto the widget.
 * Courtesy of: http://becomingindiedev.blogspot.com/2013/10/qt-5-and-sfml-20-integration.html
 *
 */

#ifndef QSFMLWidget_H
#define QSFMLWidget_H

#include <QWidget>
#include <QTimer>
#include <SFML/Graphics.hpp>

#include "State.h"

class QSFMLWidget : public QWidget, public sf::RenderWindow
{
public:
    // The default value of 0 for refreshTime will make the timer trigger a refresh whenever
    // there is no other event to process and we want the widget to refresh as many times
    // as possible for a smooth display
    explicit                QSFMLWidget(const QPoint &pos, const QSize &size, State::Context &context, QWidget *parent = 0, unsigned int refreshTime = 0);

    virtual QPaintEngine*   paintEngine() const;

    virtual void            showEvent(QShowEvent*);
    virtual void            paintEvent(QPaintEvent*);

    virtual void            onInit() = 0;
    // Over here, we pass the SFML canvas (target) and the transforms (states) to allow the
    // derived classes to draw themselves. Passing transforms allow relative rather than
    // absolute positioning of the sprites
    virtual void            onDraw(sf::RenderTarget& target, sf::RenderStates states) = 0;

    State::Context          getContext() const;

private:
    QTimer                  mRefreshTimer;
    bool                    mInitialized;

    // Context allows the widget to get resources from the resource managers
    State::Context          mContext;

    // The SFML canvas is just an SFML window without the titlebar
    sf::RenderWindow        mCanvas;
    //int i = 0;
};

#endif // QSFMLWidget_H
