/*
 * Author: King Hoe Wong
 * Desc: Implementation for title state.
 *
 */

#include "TitleState.h"
#include "ui_TitleState.h"

#include <QDebug>

TitleState::TitleState(StateStack &stack, Context &context, QWidget *parent)
    : State(stack, context, parent)
    , mUi(new Ui::TitleState)
    , mSplashScreen(QPoint(0, 0), QSize(400, 400), context)
    , mTimer(sf::Time::Zero)
{
    mUi->setupUi(this);

}

TitleState::~TitleState()
{
    delete mUi;
}

/*bool TitleState::event(QEvent *event)
{
    if (event->type() == QEvent::WindowDeactivate)
    {
        qDebug() << "Deac";
        setFocusPolicy(Qt::NoFocus);
        return true;
    }
    else if (event->type() == QEvent::WindowActivate)
    {
        qDebug() << "Ac";
        setFocusPolicy(Qt::StrongFocus);
        return true;
    }
    return false;
}*/

void TitleState::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Down)
    {
        requestStackPop();
        requestStackPush(States::ID::LoginState);
        qDebug() << "Hi";
    }
}

bool TitleState::update(const sf::Time &deltaTime)
{
    mTimer += deltaTime;
    if (mTimer.asSeconds() > 10.)
    {
        //requestStackPop();
        //requestStackPush(States::ID::LoginState);
    }
    return true;
}
