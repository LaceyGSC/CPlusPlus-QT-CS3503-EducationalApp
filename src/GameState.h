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

#include "Plantodex.h"
#include "ServerConnection.h"
#include "LevelManager.h"
#include "TileManager.h"
#include "Player.h"

#include <memory>
#include <string>

namespace Ui {
    class GameState;
}

class WorldCanvas;
class SettingsUI;
class Satchel;

class GameState : public State
{
    Q_OBJECT
public:
    struct Settings
    {
        Settings();

        bool quickTurn;
    };

    struct GameContext
    {
        GameContext(LevelManager &levelManager, TileManager &tileManager, Settings &settings, Player &player);

        LevelManager &levelManager;
        TileManager &tileManager;
        Settings &settings;
        Player &player;
    };

public:
    explicit        GameState(StateStack &stack, Context &context, QWidget *parent = 0);
                    ~GameState();

    virtual bool    update(const sf::Time &deltaTime);

    std::string     getLevelData() const;

private:
    void            registerTiles();
    void            registerLevels();

private slots:
    void            start();

    void            showPlantodex();

    void            exit();

private:
    Ui::GameState  *mUi;

    TileManager mTileManager;
    LevelManager mLevelManager;
    Settings mSettings;

    Player mPlayer;

    // Forward declaration requires these to be a pointer or reference
    std::unique_ptr<SettingsUI> mSettingsUI;
    std::unique_ptr<Satchel> mSatchel;
    // SFML sprites should be declared in the World class and drawn there
    std::unique_ptr<WorldCanvas> mWorldCanvas;

    Plantodex       mPlantodex;

    QString         packetData;
  //  Character       mCharacter;
};

#endif // GAMESTATE_H
