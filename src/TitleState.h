/*
 * Author: King Hoe Wong
 * Desc: Represents the title state for the game. Splash screen is shown here.
 *
 */

#ifndef TITLESTATE_H
#define TITLESTATE_H

#include <QWidget>
#include <QEvent>
#include <QKeyEvent>

#include "State.h"
#include "StateStack.h"
#include "SplashScreen.h"

namespace Ui {
    class TitleState;
}

class TitleState : public State
{
    Q_OBJECT

public:
    explicit        TitleState(StateStack &stack, Context &context, QWidget *parent = 0);
                    ~TitleState();

    // To disallow any event handling while the window is not active
    //virtual bool    event(QEvent *event);
    virtual void    keyPressEvent(QKeyEvent *event);

    virtual bool    update(const sf::Time &deltaTime);

private:
    Ui::TitleState  *mUi;

    SplashScreen    mSplashScreen;
    sf::Time        mTimer;
};

#endif // TITLESTATE_H
