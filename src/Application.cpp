/*
 * Author: King Hoe Wong
 * Desc: Implementation for Application class.
 * Note: Do NOT modify the .ui file for this class. The different states
 *       should have their own .ui file that can be plugged into Application.
 *       The base of a state should be a QWidget (refer to GameState.ui for
 *       an example).
 *
 */

#include "Application.h"
#include "ui_Application.h"

#include <SFML/System.hpp>

#include "StateIdentifiers.h"
#include "State.h"
#include "GameState.h"
#include "ServerConnection.h"

// 60 FPS
const sf::Time Application::TIME_PER_FRAME = sf::seconds(1.f/60.f);

Application::Application(QWidget *parent)
    : QMainWindow(parent)
    , mUi(new Ui::Application)
    , mStateStack(State::Context(mTextures))
    , mLoopTimer(this)
    , mElapsedTime(sf::Time::Zero)
    , mClock()
    , mTextures()
{
    mUi->setupUi(this);

    QMainWindow::setWindowTitle("Edu App");

    // Setup the states and push the first state
    registerStates();

    mStateStack.pushState(States::ID::LoginState);

    // Starts the game loop
    QObject::connect(&mLoopTimer, SIGNAL(timeout()), this, SLOT(gameLoop()));
    mLoopTimer.setInterval(0);
    mLoopTimer.start();
    mClock.restart();
}

Application::~Application()
{
    delete mUi;
}

// Setup all the states
void Application::registerStates()
{
    // A grid layout is used as the main layout because it centers its elements
    mStateStack.registerState<LoginState>(States::ID::LoginState, mUi->mainLayout, mUi->mainContainer);
    mStateStack.registerState<GameState>(States::ID::GameState, mUi->mainLayout, mUi->mainContainer);

}

void Application::gameLoop()
{
    // Ensures fixed time steps to prevent lagging issues (different processor speeds on different computers
    // can cause inconsistent time steps which lead to problems such as character phasing through walls)
    sf::Time deltaTime = mClock.restart();
    mElapsedTime += deltaTime;

    if (mElapsedTime > TIME_PER_FRAME)
    {
        mElapsedTime -= TIME_PER_FRAME;

        // Handle events (TODO)
        // Note: events might not need to be handled here since Qt has its own event handling system (i.e.
        // handling events by overriding the virtual functions provided by Qt)

        // Update game logic
        mStateStack.update(TIME_PER_FRAME);

        // Close window if there are no states
        if (mStateStack.isEmpty())
            this->close();
    }

    // The states should have been rendered (drawn) here. But, since drawing is handled by Qt's paint event,
    // the state stack doesn't have to explicitly call the states to draw themselves.
    // mStateStack.draw();
}
