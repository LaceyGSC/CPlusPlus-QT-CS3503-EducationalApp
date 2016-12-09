/*
 * Author: King Hoe Wong
 * Desc: Represents splash screen. Splash screen is shown using SFML.
 *
 */

#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <SFML/Graphics.hpp>

#include <QResizeEvent>

#include "QSFMLWidget.h"
#include "State.h"

class SplashScreen : public QSFMLWidget
{
public :
    explicit        SplashScreen(const QPoint &pos, const QSize &size, State::Context &context, QWidget *parent = 0);

    virtual void    onInit();
    virtual void    onDraw(sf::RenderTarget& target, sf::RenderStates states);
    virtual void    resizeEvent(QResizeEvent *event);

    virtual bool    update(const sf::Time &deltaTime);

private:
    sf::Sprite      mSprite1;
    sf::Sprite      mSprite2;
    sf::Sprite      mSprite3;
    sf::Sprite      mSprite4;

    sf::Text        mText1;
    sf::Text        mText2;
    sf::Text        mText3;

    sf::Time        mTime;

};

#endif // SPLASHSCREEN_H
