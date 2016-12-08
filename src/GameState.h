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
#include "Plantodex.h"
#include "ServerConnection.h"
#include "LevelManager.h"

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

private:
    void            createLevels();

private slots:
    void            start();

    void on_plantodexButton_clicked();

private:
    Ui::GameState  *mUi;

    // SFML sprites should be declared in the World class and drawn there
    World           mWorld;

    ServerConnection connection;
    Plantodex       mPlantodex;
<<<<<<< HEAD

    LevelManager mLevelManager;
=======
    QString         packetData;
>>>>>>> 12736ae3efb994bcdc23deafc1d93152993f3066
  //  Character       mCharacter;
};

#endif // GAMESTATE_H
