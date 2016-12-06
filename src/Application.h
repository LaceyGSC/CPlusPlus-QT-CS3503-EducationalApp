/*
 * Author: King Hoe Wong
 * Desc: Represents the application with a main window.
 * Note: Do NOT modify the .ui file for this class. The different states
 *       should have their own .ui file that can be plugged into Application.
 *       The base of a state should be a QWidget (refer to TitleState.ui for
 *       an example).
 *
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <QTimer>
#include <SFML/System.hpp>

#include "StateStack.h"
#include "ResourceIdentifiers.h"
#include "ResourceManager.h"

// Forward declaration
namespace Ui
{
    class Application;
}

class Application : public QMainWindow
{
    Q_OBJECT

public:
    explicit                Application(QWidget *parent = 0);
                            ~Application();

private:
    // Setup all the game states
    void                    registerStates();

private slots:
    // The main game loop. This is where events and game logic are handled
    void                    gameLoop();

private:
    // Game FPS
    static const sf::Time   TIME_PER_FRAME;

    // Main window ui
    Ui::Application         *mUi;

    // A stack of states eases the transition between game states.
    StateStack              mStateStack;

    // Used for the game loop
    QTimer                  mLoopTimer;

    // Used in ensuring fixed time steps
    sf::Time                mElapsedTime;
    sf::Clock               mClock;

    // Resource managers
    TextureManager          mTextures;
    FontManager             mFonts;
};

#endif // APPLICATION_H
