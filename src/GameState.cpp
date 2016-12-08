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
    , mPlantodex()
    , mLevelManager()
{
    mUi->setupUi(this);

    createLevels();
    mLevelManager.nextLevel();
    mUi->levelLabel->setText(mLevelManager.getCurrentLevel().getName());

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

    std::unique_ptr<Level> level1(new Level("Level 1: A New Seed", mUi->levelContainer));
    mUi->formLayout->addWidget(&(*level1));



    std::unique_ptr<Quest> quest(new Quest("So, you want to be a plant expert?", &*level1));

    SQCollectProperties::DataPtr data1(new SQCollectProperties::Data("Mosquitos are pesky little creatures. Gather 15 plants to fend them off.",
                                                                     Plant::Properties::InsectRepellent, 15));

    Quest::SubQuestPtr subQ(new SQCollectProperties(std::move(data1), &*quest));

    quest->addSubQuest(std::move(subQ));




    level1->addMainQuest(std::move(quest));




    quest.reset(new Quest("The Harvester", &*level1));

    SQCollectSpecific::DataPtr data2(new SQCollectSpecific::Data("Gather at 8 lavenders.",
                                                                 Plant::ID::Lavender, 8));

    subQ.reset(new SQCollectSpecific(std::move(data2), &*quest));

    quest->addSubQuest(std::move(subQ));

    data2.reset(new SQCollectSpecific::Data("Gather at 15 cattails.",
                                                                 Plant::ID::Cattail, 15));

    subQ.reset(new SQCollectSpecific(std::move(data2), &*quest));

    quest->addSubQuest(std::move(subQ));

    data2.reset(new SQCollectSpecific::Data("Gather at 8 catnips.",
                                                                 Plant::ID::Catnip, 7));

    subQ.reset(new SQCollectSpecific(std::move(data2), &*quest));

    quest->addSubQuest(std::move(subQ));




    level1->addMainQuest(std::move(quest));





    quest.reset(new Quest("Knowledge is power", &*level1));

    SQCollectType::DataPtr data3(new SQCollectType::Data("Gather at least 3 different species of plants.", 3));

    subQ.reset(new SQCollectType(std::move(data3), &*quest));

    quest->addSubQuest(std::move(subQ));




    level1->addOptionalQuest(std::move(quest));





    mLevelManager.addLevel(std::move(level1));










    level1.reset(new Level("Level 2: Growing Sprout", mUi->levelContainer));
    mUi->formLayout->addWidget(&(*level1));



    quest.reset(new Quest("So, you want to be a plant expert?", &*level1));

    data1.reset(new SQCollectProperties::Data("Mosquitos are pesky little creatures. Gather 15 plants to fend them off.",
                                                                     Plant::Properties::InsectRepellent, 15));

    subQ.reset(new SQCollectProperties(std::move(data1), &*quest));

    quest->addSubQuest(std::move(subQ));




    level1->addMainQuest(std::move(quest));


    mLevelManager.addLevel(std::move(level1));
}

void GameState::start()
{
    if (mWorld.isHidden())
    {
        mUi->worldContainer->addWidget(&mWorld);
      //  mUi->worldContainer->addWidget(&mCharacter);
        mWorld.show();
        //qDebug().noquote() << connection.getPacket();

        //PickUp c(Plant::ID::Catnip, 1);


        //    qDebug() << c.amount;

        mLevelManager.prevLevel();
        mUi->levelLabel->setText(mLevelManager.getCurrentLevel().getName());

        mLevelManager.getCurrentLevel().update(&PickUp(Plant::ID::Catnip, Plant::Properties::None, 1));
    }
    else
    {
        mUi->worldContainer->removeWidget(&mWorld);
        mWorld.hide();

        mLevelManager.nextLevel();
        mUi->levelLabel->setText(mLevelManager.getCurrentLevel().getName());

        mLevelManager.getCurrentLevel().update(&PickUp(Plant::ID::Lavender, Plant::Properties::InsectRepellent, 1));
        mLevelManager.getCurrentLevel().update(&PickUp(Plant::ID::Cattail, Plant::Properties::None, 3));
    }

    if (mLevelManager.getCurrentLevel().isMainCompleted())
        qDebug() << "Main Completed!";

    if (mLevelManager.getCurrentLevel().isOptionalCompleted())
        qDebug() << "Optional Completed!";
}

void GameState::on_plantodexButton_clicked()
{
    mPlantodex.show();
}
