/*
 * Author: King Hoe Wong
 * Desc: Implementation for GameState.
 *
 */

#include "GameState.h"
#include "ui_GameState.h"

#include <SFML/Graphics.hpp>
#include <QWidget>
#include <QDebug>

#include "State.h"
#include "StateStack.h"
#include "ResourceIdentifiers.h"
#include "ResourceManager.h"
#include "World.h"


GameState::GameState(StateStack &stack, Context &context, QWidget *parent)
    : State(stack, context, parent)
    , mUi(new Ui::GameState)
    , mWorld(QPoint(0, 0), QSize(400, 400), context)
    , mPlantodex()
{
    mUi->setupUi(this);

    // Display the game state widget
    this->show();

    // Start the MySQL connection
    connection.sendPacket("Select * from PlantDatabase");

    // Sets the column ratio for World : charStats to 3 : 1

    mUi->gameContainer->setColumnStretch(0, 3);
    mUi->gameContainer->setColumnStretch(1, 1);

    // Set parent to allow the canvas to be displayed with reference to its container
    mWorld.setParent(mUi->worldBox);
    QObject::connect(mUi->pushButton, SIGNAL(pressed()), this, SLOT(start()));
    mWorld.hide();
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
    if (mWorld.isHidden())
    {
        mUi->worldContainer->addWidget(&mWorld);
      //  mUi->worldContainer->addWidget(&mCharacter);
        mWorld.show();
        qDebug().noquote() << connection.getPacket();
    }
    else
    {
        mUi->worldContainer->removeWidget(&mWorld);
        mWorld.hide();
    }
}

void GameState::on_plantodexButton_clicked()
{
    mPlantodex.show();
}
