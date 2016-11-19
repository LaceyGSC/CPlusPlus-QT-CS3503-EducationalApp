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

#include "SFMLCanvas.h"

namespace Ui {
    class TitleState;
}

class TitleState : public State
{
    Q_OBJECT

public:
    explicit        TitleState(StateStack &stack, Context &context, QWidget *parent = 0);
                    ~TitleState();

    virtual bool    update(const sf::Time &deltaTime);

private slots:
    void            start();

private:
    Ui::TitleState  *mUi;

    // SFML sprites can be drawn onto the canvas
    SFMLCanvas      mCanvas;
};

#endif // TITLESTATE_H
