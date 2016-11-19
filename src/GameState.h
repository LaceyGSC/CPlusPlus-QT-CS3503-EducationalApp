/*
 * Author: King Hoe Wong
 * Desc: Represents a game state (playing state).
 *
 */

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QWidget>

#include "State.h"
#include "StateStack.h"

#include "WorldCanvas.h"

namespace Ui {
    class GameState;
}

class GameState : public State
{
    Q_OBJECT

public:
    explicit        GameState(StateStack &stack, Context &context, QWidget *parent = 0);
                    ~GameState();

    virtual bool    update(const sf::Time &deltaTime);

private slots:
    void            start();

private:
    Ui::GameState  *mUi;

    // SFML sprites can be drawn onto the canvas
    WorldCanvas      mCanvas;
};

#endif // GAMESTATE_H
