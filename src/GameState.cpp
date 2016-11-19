/*
 * Author: King Hoe Wong
 * Desc: Implementation for GameState.
 *
 */

#include "GameState.h"
#include "ui_GameState.h"

#include <SFML/Graphics.hpp>
#include <QWidget>

#include "State.h"
#include "StateStack.h"
#include "ResourceIdentifiers.h"
#include "ResourceManager.h"
#include "WorldCanvas.h"

GameState::GameState(StateStack &stack, Context &context, QWidget *parent)
    : State(stack, context, parent)
    , mUi(new Ui::GameState)
    , mCanvas(QPoint(0, 0), QSize(400, 400), context)
{
    mUi->setupUi(this);

    // Display the game state widget
    this->show();

    // Sets the column ratio for worldCanvas : charStats to 3 : 1
    mUi->gameContainer->setColumnStretch(0, 3);
    mUi->gameContainer->setColumnStretch(1, 1);

    mCanvas.setParent(mUi->worldBox);

    QObject::connect(mUi->pushButton, SIGNAL(pressed()), this, SLOT(start()));
    mCanvas.hide();
}

GameState::~GameState()
{
    delete mUi;
}


bool GameState::update(const sf::Time &deltaTime)
{
    return true;
}

void GameState::start()
{
    if (mCanvas.isHidden())
    {
        mUi->worldContainer->addWidget(&mCanvas);
        mCanvas.show();
    }
    else
    {
        mUi->worldContainer->removeWidget(&mCanvas);
        mCanvas.hide();
    }
}
