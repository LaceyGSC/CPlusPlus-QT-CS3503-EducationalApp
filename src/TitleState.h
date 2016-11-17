/*
 * Author: King Hoe Wong
 * Desc: Represents a title state (or splash screen).
 *
 */

#ifndef TITLESTATE_H
#define TITLESTATE_H

#include <QWidget>

#include "State.h"
#include "StateStack.h"

namespace Ui {
    class TitleState;
}

class TitleState : public State
{
    Q_OBJECT

public:
    explicit        TitleState(StateStack& stack, QWidget *parent = 0);
                    ~TitleState();

    virtual bool    update(const sf::Time &deltaTime);

private:
    Ui::TitleState  *mUi;
};

#endif // TITLESTATE_H
