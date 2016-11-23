/*
 * Author: King Hoe Wong
 * Desc: Represents a game state (playing state). This class should contain all the
 *       gameplay-related data such as the world data, player data, etc..
 *
 */

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QWidget>

#include "State.h"
#include "StateStack.h"

#include "World.h"

#include "ServerConnection.h"

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

    // SFML sprites should be declared in the World class and drawn there
    World           mWorld;

    ServerConnection connection;
};

#endif // GAMESTATE_H
