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

#include "Identifiers.h"
#include "State.h"
#include "TitleState.h"
#include "GameState.h"
#include "LoginState.h"
#include "AdminState.h"
#include "ServerConnection.h"

// 60 FPS
const sf::Time Application::TIME_PER_FRAME = sf::seconds(1.f/60.f);

Application::Application(QWidget *parent)
    : QMainWindow(parent)
    , mUi(new Ui::Application)
    , mManual(new ManualDialog(this))
    , mLoopTimer(this)
    , mElapsedTime(sf::Time::Zero)
    , mClock()
    , mTextures()
    , mFonts()
    , mSounds()
    , mMusic()
    , mStateStack(State::Context(mTextures, mFonts, mSounds, mMusic, mConnection))
{
    mUi->setupUi(this);

    QMainWindow::setWindowTitle("PlantQuest");

    mManual->setWindowFlags(mManual->windowFlags() &= ~Qt::WindowContextHelpButtonHint);
    mManual->setWindowTitle("PlantQuest Manual");
    mManual->hide();

    // Setup the states and push the first state
    registerStates();

    loadTextures();

    mStateStack.pushState(States::ID::TitleState);

    // Starts the game loop
    QObject::connect(&mLoopTimer, SIGNAL(timeout()), this, SLOT(gameLoop()));
    mLoopTimer.setInterval(0);
    mLoopTimer.start();
    mClock.restart();

    QObject::connect(mUi->actionManual, SIGNAL(triggered(bool)), this, SLOT(onManual()));
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
    mStateStack.registerState<LoginState>(States::ID::LoginState, mUi->mainLayout, mUi->mainContainer);
    mStateStack.registerState<AdminState>(States::ID::AdminState, mUi->mainLayout, mUi->mainContainer);
    mStateStack.registerState<GameState>(States::ID::GameState, mUi->mainLayout, mUi->mainContainer);
}

void Application::loadTextures()
{
    mTextures.load(Tiles::ID::Bridge             , "qrc:/../media/Textures/Bridge.png");
    mTextures.load(Tiles::ID::Catnip             , "qrc:/../media/Textures/sprite_catnip-01.png");
    mTextures.load(Tiles::ID::Cattail            , "qrc:/../media/Textures/sprite_cattail-01.png");
    mTextures.load(Tiles::ID::DeepFreshWater     , "qrc:/../media/Textures/DeepFreshWater.png");
    mTextures.load(Tiles::ID::DeepSaltWater      , "qrc:/../media/Textures/DeepSaltWater.png");
    mTextures.load(Tiles::ID::Dirt               , "qrc:/../media/Textures/Dirt.png");
    mTextures.load(Tiles::ID::Fire               , "qrc:/../media/Textures/Fire.png");
    mTextures.load(Tiles::ID::Grass              , "qrc:/../media/Textures/Grass.png");
    mTextures.load(Tiles::ID::Lavender           , "qrc:/../media/Textures/sprite_lavender-01.png");
    mTextures.load(Tiles::ID::Mountain           , "qrc:/../media/Textures/Mountain.png");
    mTextures.load(Tiles::ID::QuickSand          , "qrc:/../media/Textures/Quicksand.png");
    mTextures.load(Tiles::ID::RedSand            , "qrc:/../media/Textures/RedSand.png");
    mTextures.load(Tiles::ID::Sand               , "qrc:/../media/Textures/Sand.png");
    mTextures.load(Tiles::ID::ShallowFreshWater  , "qrc:/../media/Textures/ShallowFreshWater.png");
    mTextures.load(Tiles::ID::ShallowSaltWater   , "qrc:/../media/Textures/ShallowSaltWater.png");
    mTextures.load(Tiles::ID::Tree               , "qrc:/../media/Textures/Tree.png");

    mTextures.load(Tiles::ID::FaceUp             , "qrc:/../media/Textures/up.png");
    mTextures.load(Tiles::ID::FaceDown           , "qrc:/../media/Textures/down.png");
    mTextures.load(Tiles::ID::FaceRight          , "qrc:/../media/Textures/right.png");
    mTextures.load(Tiles::ID::FaceLeft           , "qrc:/../media/Textures/left.png");

    mTextures.load(Tiles::ID::Satchel            , "qrc:/../media/Textures/Satchel.png");


    mTextures.get(Tiles::ID::Satchel).setSmooth(true);
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

void Application::onManual()
{
    mManual->show();
}
