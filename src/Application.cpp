/*
 * Author: King Hoe Wong
 * Desc: Implementation for Application class.
 * Note: Do NOT modify the .ui file for this class. The different states
 *       should have their own .ui file that can be plugged into Application.
 *       The base of a state should be a QWidget (refer to TitleState.ui for
 *       an example).
 *
 */

#include "Application.h"
#include "ui_Application.h"

#include <SFML/System.hpp>

#include "StateIdentifiers.h"
#include "TitleState.h"
#include "mysqlconnection.h"

// 60 FPS
const sf::Time Application::TIME_PER_FRAME = sf::seconds(1.f/60.f);

Application::Application(QWidget *parent)
    : QMainWindow(parent)
    , mUi(new Ui::Application)
    , mStateStack()
    , mLoopTimer(this)
    , mElapsedTime(sf::Time::Zero)
    , mClock()
{
    mUi->setupUi(this);

    QMainWindow::setWindowTitle("Edu App");

    MySQLConnection();

    // Setup the states and push the first state
    registerStates();
    mStateStack.pushState(States::ID::TitleState);

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
    mStateStack.registerState<TitleState>(States::ID::TitleState, mUi->mainLayout, mUi->mainContainer);
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
