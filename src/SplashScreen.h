/*
 * Author: King Hoe Wong
 * Desc: Represents splash screen. Splash screen is shown using SFML.
 *
 */

#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <SFML/Graphics.hpp>

#include "QSFMLWidget.h"
#include "State.h"

class SplashScreen : public QSFMLWidget
{
public :
    explicit        SplashScreen(const QPoint &pos, const QSize &size, State::Context &context, QWidget *parent = 0);

    virtual void    onInit();
    virtual void    onDraw(sf::RenderTarget& target, sf::RenderStates states);

private:

};

#endif // SPLASHSCREEN_H
