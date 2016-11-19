/*
 * Author: King Hoe Wong
 * Desc: Implementation of abstract class QSFMLWidget.
 * Courtesy of: http://becomingindiedev.blogspot.com/2013/10/qt-5-and-sfml-20-integration.html
 *
 */

#include "QSFMLWidget.h"

#ifdef Q_WS_X11
#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
#endif

#include "State.h"

QSFMLWidget::QSFMLWidget(const QPoint &pos, const QSize &size, State::Context &context, QWidget *parent, unsigned int refreshTime)
    : QWidget(parent)
    , mInitialized(false)
    , mRefreshTimer(this)
    , mContext(context)
{
    // Tells Qt that we will not use its painting functions, and paint directly onto the widget
    QWidget::setAttribute(Qt::WA_PaintOnScreen);

    // Prevents from drawing the widget's background, which could cause some flickering
    QWidget::setAttribute(Qt::WA_OpaquePaintEvent);
    QWidget::setAttribute(Qt::WA_NoSystemBackground);

    // Set strong focus to enable keyboard events to be received
    QWidget::setFocusPolicy(Qt::StrongFocus);

    // Setup the widget geometry
    QWidget::move(pos);
    QWidget::resize(size);

    // Setup the refresh timer
    mRefreshTimer.setInterval(refreshTime);
}

// Tells Qt that we're not using any of its built-in paint engines
QPaintEngine* QSFMLWidget::paintEngine() const
{
    return 0;
}


void QSFMLWidget::showEvent(QShowEvent*)
{
    if (!mInitialized)
    {
        // Under X11, we need to flush the commands sent to the server to ensure that
        // SFML will get an updated view of the windows
        #ifdef Q_WS_X11
            XFlush(QX11Info::display());
        #endif

        // Create the SFML window with the widget handle
        sf::RenderWindow::create((sf::WindowHandle)(winId()));

        // Let the derived class do its specific stuff
        onInit();

        // Setup the timer to trigger a refresh at specified refresh rate
        QObject::connect(&mRefreshTimer, SIGNAL(timeout()), this, SLOT(repaint()));
        mRefreshTimer.start();
        mInitialized = true;
    }
}

void QSFMLWidget::paintEvent(QPaintEvent*)
{
    // Clear screen
    sf::RenderWindow::clear(sf::Color::Transparent);

    // Let the derived class do its specific stuff
    onDraw();

    // Display on screen
    sf::RenderWindow::display();
}

State::Context QSFMLWidget::getContext() const
{
    return mContext;
}
