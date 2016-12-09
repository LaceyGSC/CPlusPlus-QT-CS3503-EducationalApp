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
    , mSplashScreen(QPoint(0, 0), QSize(parent->size()), context)
    , mTime(sf::Time::Zero)
{
    mUi->setupUi(this);

    // Display the title state widget
    this->show();

    // Make the window active so that it can receive events
    this->activateWindow();

    // Enable keyboard events
    setFocusPolicy(Qt::StrongFocus);

    mSplashScreen.setParent(mUi->mainContainer);
    mSplashScreen.show();
}

TitleState::~TitleState()
{
    delete mUi;
}

// To disallow any event handling while the window is not active
bool TitleState::event(QEvent *event)
{
    if (event->type() == QEvent::WindowDeactivate)
        setFocusPolicy(Qt::NoFocus);
    else if (event->type() == QEvent::WindowActivate)
        setFocusPolicy(Qt::StrongFocus);

    return QWidget::event(event);
}

void TitleState::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        requestStackPop();
        requestStackPush(States::ID::LoginState);
    }
}

void TitleState::resizeEvent(QResizeEvent *event)
{
    mSplashScreen.resize(event->size());
}

bool TitleState::update(const sf::Time &deltaTime)
{
    mTime += deltaTime;
    if (mTime.asSeconds() > 8.)
    {
        requestStackPop();
        requestStackPush(States::ID::LoginState);
    }
    return mSplashScreen.update(deltaTime);
}
