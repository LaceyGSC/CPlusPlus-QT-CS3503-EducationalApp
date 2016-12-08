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
#include "Quest.h"
#include "Commands.h"
#include "SQCollectSpecific.h"
#include "SQCollectProperties.h"
#include "SQCollectType.h"


GameState::GameState(StateStack &stack, Context &context, QWidget *parent)
    : State(stack, context, parent)
    , mUi(new Ui::GameState)
    , mWorld(QPoint(0, 0), QSize(400, 400), context)
<<<<<<< HEAD
    , mPlantodex()
    , mLevelManager()
=======
>>>>>>> 12736ae3efb994bcdc23deafc1d93152993f3066
{
    mUi->setupUi(this);

    createLevels();
    mLevelManager.nextLevel();

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

    LevelManager::LevelPtr level1(new Level("Level 1: A New Seed", mLevelManager, mUi->levelContainer));
    mUi->formLayout->addWidget(&(*level1));



    Level::QuestPtr quest(new Quest("So, you want to be a plant expert?", &*level1));

    Quest::SubQuestPtr subQ(new SQCollectProperties("Mosquitos are pesky little creatures. Gather 15 plants to fend them off.",
                                                    Plant::Properties::InsectRepellent, 15, &*quest));

    quest->addSubQuest(std::move(subQ));



    level1->addMainQuest(std::move(quest));




    quest.reset(new Quest("The Harvester", &*level1));


    subQ.reset(new SQCollectSpecific("Gather 8 lavenders.",
                                     Plant::ID::Lavender, 8, &*quest));

    quest->addSubQuest(std::move(subQ));

    subQ.reset(new SQCollectSpecific("Gather 15 cattails.",
                                     Plant::ID::Cattail, 15, &*quest));

    quest->addSubQuest(std::move(subQ));

    subQ.reset(new SQCollectSpecific("Gather 7 catnips.",
                                     Plant::ID::Catnip, 7, &*quest));

    quest->addSubQuest(std::move(subQ));


    level1->addMainQuest(std::move(quest));



    Level::RewardPtr reward(new Reward("+ 150 points", &*level1));

    reward->setOnActivate([&] ()
    {
        qDebug() << "Rewarded Main!";
    });


    level1->setRewardMain(std::move(reward));




    quest.reset(new Quest("Knowledge is power", &*level1));

    subQ.reset(new SQCollectType("Gather at least 3 different species of plants.", 3, &*quest));

    quest->addSubQuest(std::move(subQ));



    level1->addOptionalQuest(std::move(quest));


    reward.reset(new Reward("+ Quick Plant Analyzer \n+ 50 points", &*level1));

    reward->setOnActivate([&] ()
    {
        qDebug() << "Rewarded Optional!";
    });


    level1->setRewardOptional(std::move(reward));



    mLevelManager.addLevel(std::move(level1));










    level1.reset(new Level("Level 2: Growing Sprout", mLevelManager, mUi->levelContainer));
    mUi->formLayout->addWidget(&(*level1));



    quest.reset(new Quest("So, you want to be a plant expert?", &*level1));

    subQ.reset(new SQCollectProperties("Mosquitos are pesky little creatures. Gather 15 plants to fend them off.",
                                       Plant::Properties::InsectRepellent, 15, &*quest));

    quest->addSubQuest(std::move(subQ));




    level1->addMainQuest(std::move(quest));



    reward.reset(new Reward("+ Quick Plant Analyzer \n+ 50 points", &*level1));

    reward->setOnActivate([&] ()
    {
        qDebug() << "Rewarded Main!";
    });


    level1->setRewardMain(std::move(reward));



    mLevelManager.addLevel(std::move(level1));
}

void GameState::start()
{
    if (mWorld.isHidden())
    {
        mUi->worldContainer->addWidget(&mWorld);

        mWorld.show();
<<<<<<< HEAD

        //mLevelManager.prevLevel();
        //mUi->levelLabel->setText(mLevelManager.getCurrentLevel().getName());

        mLevelManager.getCurrentLevel().update(&PickUp(Plant::ID::Catnip, Plant::Properties::None, 1));
        mLevelManager.getCurrentLevel().update(&PickUp(Plant::ID::Lavender, Plant::Properties::InsectRepellent, 1));
        mLevelManager.getCurrentLevel().update(&PickUp(Plant::ID::Cattail, Plant::Properties::None, 3));
=======
        packetData =  connection.getPacket();
        mPlantodex.setUpPlantodex(&packetData);

>>>>>>> 12736ae3efb994bcdc23deafc1d93152993f3066
    }
    else
    {
        mUi->worldContainer->removeWidget(&mWorld);
        mWorld.hide();

        //mLevelManager.nextLevel();
        //mUi->levelLabel->setText(mLevelManager.getCurrentLevel().getName());
    }
}

void GameState::on_plantodexButton_clicked()
{
    mPlantodex.show();
}
