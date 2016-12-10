/*
 * Author: King Hoe Wong
 * Desc: Implementation for splash screen.
 *
 */

#include "SplashScreen.h"

#include "ResourceManager.h"
#include "Identifiers.h"

 #include <QDebug>

SplashScreen::SplashScreen(const QPoint &pos, const QSize &size, State::Context &context, QWidget *parent)
    : QSFMLWidget(pos, size, context, parent)
    , mSprite1()
    , mSprite2()
    , mSprite3()
    , mSprite4()
    , mText1()
    , mText2()
    , mText3()
    , mTime(sf::Time::Zero)
{
}

void SplashScreen::onInit()
{
    getContext().textures.load(Tiles::ID::TitleLogo, "qrc:/../media/Textures/TitleLogo.png");
    getContext().textures.get(Tiles::ID::TitleLogo).setSmooth(true);

    mSprite4.setTexture(getContext().textures.get(Tiles::ID::TitleLogo));
    mSprite4.setOrigin(mSprite4.getLocalBounds().width / 2, mSprite4.getLocalBounds().height / 2);
    mSprite4.setPosition(width() / 2, 1.5 * height() / 9);
    mSprite4.setScale(0.3f, 0.3f);

    getContext().fonts.load(Fonts::ID::SplashScreenFont, "qrc:/../media/Fonts/ARHERMANN.ttf");

    //sf::String string("An Educational Application", getContext().fonts.get((int)Fonts::ID::SplashScreenFont), 30u);
    /*mText1.setFont(getContext().fonts.get((int)Fonts::ID::SplashScreenFont));
    mText1.setString("An Educational Application");
    mText1.setColor(sf::Color::Black);
    mText1.setCharacterSize(250u);
    mText1.setScale(0.1, 0.1);
    mText1.setOrigin(mText1.getLocalBounds().width / 2, mText1.getLocalBounds().height / 2);
    mText1.setPosition(width() / 2, height() / 9);*/

    mText2.setFont(getContext().fonts.get(Fonts::ID::SplashScreenFont));
    mText2.setString("made using");
    mText2.setColor(sf::Color::Black);
    mText2.setCharacterSize(200u);
    mText2.setScale(0.1f, 0.1f);
    mText2.setOrigin(mText2.getLocalBounds().width / 2, mText2.getLocalBounds().height / 2);
    mText2.setPosition(width() / 2, 3.5 * height() / 9);

    getContext().textures.load(Tiles::ID::SFMLLogo, "qrc:/../media/Textures/SFMLLogo.png");
    getContext().textures.get(Tiles::ID::SFMLLogo).setSmooth(true);

    mSprite1.setTexture(getContext().textures.get(Tiles::ID::SFMLLogo));
    mSprite1.setOrigin(mSprite1.getLocalBounds().width / 2, mSprite1.getLocalBounds().height / 2);
    mSprite1.setPosition(width() / 4, 4.75 * height() / 9);
    mSprite1.setScale(0.2f, 0.2f);

    getContext().textures.load(Tiles::ID::Box2DLogo, "qrc:/../media/Textures/Box2DLogo.png");
    getContext().textures.get(Tiles::ID::Box2DLogo).setSmooth(true);

    mSprite2.setTexture(getContext().textures.get(Tiles::ID::Box2DLogo));
    mSprite2.setOrigin(mSprite2.getLocalBounds().width / 2, mSprite2.getLocalBounds().height / 2);
    mSprite2.setPosition(2 * width() / 4, 4.75 * height() / 9);
    mSprite2.setScale(0.3f, 0.3f);

    getContext().textures.load(Tiles::ID::QtLogo, "qrc:/../media/Textures/QtLogo.png");
    getContext().textures.get(Tiles::ID::QtLogo).setSmooth(true);

    mSprite3.setTexture(getContext().textures.get(Tiles::ID::QtLogo));
    mSprite3.setOrigin(mSprite3.getLocalBounds().width / 2, mSprite3.getLocalBounds().height / 2);
    mSprite3.setPosition(3 * width() / 4, 4.75 * height() / 9);
    mSprite3.setScale(0.3f, 0.3f);

    mText3.setFont(getContext().fonts.get(Fonts::ID::SplashScreenFont));
    mText3.setString("by");
    mText3.setColor(sf::Color::Black);
    mText3.setCharacterSize(200u);
    mText3.setScale(0.1f, 0.1f);
    mText3.setOrigin(mText3.getLocalBounds().width / 2, mText3.getLocalBounds().height / 2);
    mText3.setPosition(width() / 2, 6.25 * height() / 9);

    mText1.setFont(getContext().fonts.get(Fonts::ID::SplashScreenFont));
    mText1.setString("#00FF00");
    mText1.setColor(sf::Color::Black);
    mText1.setCharacterSize(250u);
    mText1.setScale(0.1f, 0.1f);
    mText1.setOrigin(mText1.getLocalBounds().width / 2, mText1.getLocalBounds().height / 2);
    mText1.setPosition(width() / 2, 7.5 * height() / 9);
    //mText.setScale(0.1, 0.1);
    /*getContext().textures.load((int)Textures::ID::TitleLogo, "qrc:/../media/Textures/TitleLogo.png");
    getContext().textures.get((int)Textures::ID::TitleLogo).setSmooth(true);

    mTitleSprite.setTexture(getContext().textures.get((int)Textures::ID::TitleLogo));
    mTitleSprite.setOrigin(mTitleSprite.getLocalBounds().width / 2, mTitleSprite.getLocalBounds().height / 2);
    mTitleSprite.setPosition(width() / 2, height() / 2);
    mTitleSprite.setScale((double)size().width() / (double)getContext().textures.get((int)Textures::ID::TitleLogo).getSize().x,
                          (double)size().height() / (double)getContext().textures.get((int)Textures::ID::TitleLogo).getSize().y);

    qDebug() << getContext().textures.get((int)Textures::ID::TitleLogo).getSize().x;
    qDebug() << size().width();*/

    //mText1.setFillColor(sf::Color(255, 255, 255, 0));
    //mText2.setFillColor(sf::Color(255, 255, 255, 0));
    //mText3.setFillColor(sf::Color(255, 255, 255, 0));
    mSprite1.setColor(sf::Color(255, 255, 255, 0));
    mSprite2.setColor(sf::Color(255, 255, 255, 0));
    mSprite3.setColor(sf::Color(255, 255, 255, 0));
    mSprite4.setColor(sf::Color(255, 255, 255, 0));
}

void SplashScreen::onDraw(sf::RenderTarget& target, sf::RenderStates states)
{
    //mTitleSprite.setPosition(width() / 2, height() / 2);
    target.clear(sf::Color::White);
    target.draw(mSprite1, states);
    target.draw(mSprite2, states);
    target.draw(mSprite3, states);
    target.draw(mSprite4, states);
    target.draw(mText1, states);
    target.draw(mText2, states);
    target.draw(mText3, states);
    //target.draw(mTitleSprite, states);
}

void SplashScreen::resizeEvent(QResizeEvent *event)
{
    QSFMLWidget::resizeEvent(event);
    //mCanvas.setPosition(sf::Vector2i(event->size().width() / 2 - mCanvas.getSize().x / 2, event->size().height() / 2 - mCanvas.getSize().y / 2));
    //setStyleSheet("background-color:white;");

    #ifndef __APPLE__
    mCanvas.setSize(sf::Vector2u(event->size().width(), event->size().height())); //this line causes gaurenteed crashes on open
    #endif
}

bool SplashScreen::update(const sf::Time &deltaTime)
{
    mTime += deltaTime;
    if (mTime.asSeconds() > 1.)
    {
        mSprite1.setColor(mSprite1.getColor() + sf::Color(255, 255, 255, 2));
        mSprite2.setColor(mSprite2.getColor() + sf::Color(255, 255, 255, 2));
        mSprite3.setColor(mSprite3.getColor() + sf::Color(255, 255, 255, 2));
        mSprite4.setColor(mSprite4.getColor() + sf::Color(255, 255, 255, 2));
        //mText1.setFillColor(mText1.getFillColor() + sf::Color(255, 255, 255, 2));
        //mText2.setFillColor(mText2.getFillColor() + sf::Color(255, 255, 255, 2));
        //mText3.setFillColor(mText3.getFillColor() + sf::Color(255, 255, 255, 2));
    }
    return true;
}
