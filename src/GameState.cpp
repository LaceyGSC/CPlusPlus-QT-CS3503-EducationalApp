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
#include "CollectionQ.h"


GameState::GameState(StateStack &stack, Context &context, QWidget *parent)
    : State(stack, context, parent)
    , mUi(new Ui::GameState)
    , mWorld(QPoint(0, 0), QSize(400, 400), context)
    , mPlantodex()
    , mLevels()
{
    mUi->setupUi(this);

    createLevels();

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

void GameState::createLevels()
{

    std::unique_ptr<Level> level1(new Level(mUi->levelContainer));
    mUi->formLayout->addWidget(&(*level1));

    /*std::unique_ptr<Quest> quest(new CollectionQ("So, you want to be a plant expert?",
                                                 "Mosquitos are pesky little creatures. Gather 15 plants to fend them off.", &(*(level1))));

    std::unique_ptr<CollectionQ::Ptr> data(new CollectionQ::Ptr(20, ))

    quest->addData(Plant::ID::Lavender, )*/

    level1->addQuest(std::unique_ptr<Quest>(new CollectionQ("So, you want to be a plant expert?",
                                                      "Mosquitos are pesky little creatures. Gather 15 plants to fend them off.", &(*(level1)))));

    level1->addQuest(std::unique_ptr<Quest>(new CollectionQ("Knowledge is power",
                                                      "Gather at least 8 different species of plants.", &(*(level1)))));

    mLevels.push_back(std::move(level1));

    mUi->levelLabel->setText("Level 1: A New Seed");
}

void GameState::start()
{
    if (mWorld.isHidden())
    {
        mUi->worldContainer->addWidget(&mWorld);
      //  mUi->worldContainer->addWidget(&mCharacter);
        mWorld.show();
        //qDebug().noquote() << connection.getPacket();
        mLevels.back()->mQuests.back()->setCompletion(mLevels.back()->mQuests.back()->getCompletion() + 5);
    }
    else
    {
        mUi->worldContainer->removeWidget(&mWorld);
        mWorld.hide();
        mLevels.back()->mQuests.front()->setCompletion(mLevels.back()->mQuests.front()->getCompletion() + 5);
    }

    if (mLevels.back()->isCompleted())
        qDebug() << "Completed!";
}

void GameState::on_plantodexButton_clicked()
{
    mPlantodex.show();
}
