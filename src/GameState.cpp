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
#include <QMetaEnum>

#include "State.h"
#include "StateStack.h"
#include "Identifiers.h"
#include "ResourceManager.h"
#include "WorldCanvas.h"
#include "Quest.h"
#include "Commands.h"
#include "SQCollectSpecific.h"
#include "SQCollectProperties.h"
#include "SQCollectType.h"
#include "SettingsUI.h"
#include "Satchel.h"

#include <vector>

GameState::Settings::Settings()
    : quickTurn(true)
{
}

GameState::GameContext::GameContext(LevelManager &levelManager, TileManager &tileManager, Settings &settings, Player &player)
    : levelManager(levelManager)
    , tileManager(tileManager)
    , settings(settings)
    , player(player)
{
}

GameState::GameState(StateStack &stack, Context &context, QWidget *parent)
    : State(stack, context, parent)
    , mUi(new Ui::GameState)
    , mTileManager()
    , mLevelManager()
    , mSettings()
    , mPlayer()
    , mSettingsUI(new SettingsUI(GameContext(mLevelManager, mTileManager, mSettings, mPlayer)))
    , mSatchel(new Satchel(context, GameContext(mLevelManager, mTileManager, mSettings, mPlayer)))
    , mWorldCanvas(new WorldCanvas(QPoint(0, 0), QSize(400, 400), context, GameContext(mLevelManager, mTileManager, mSettings, mPlayer), &*mSatchel))
    , mPlantodex()
{   
    mUi->setupUi(this);

    registerTiles();

    registerLevels();

    // Start level
    mLevelManager.nextLevel();

    // Display the game state widget
    this->show();

    // Sets the column ratio to 1 : 3 : 1 : 2
    mUi->gameContainer->setColumnStretch(0, 1);
    mUi->gameContainer->setColumnStretch(1, 2);
    mUi->gameContainer->setColumnStretch(2, 1);
    mUi->gameContainer->setColumnStretch(3, 2);

    QObject::connect(mUi->pushButton, SIGNAL(pressed()), this, SLOT(start()));
    QObject::connect(mUi->plantodexButton, SIGNAL(pressed()), this, SLOT(showPlantodex()));
    QObject::connect(mUi->exit, SIGNAL(pressed()), this, SLOT(exit()));

    // Make the world container the same size as the world
    mUi->worldBox->setMinimumSize(mWorldCanvas->minimumSize());

    // Allows the canvas to be displayed with reference to its container
    mWorldCanvas->setParent(mUi->worldBox);
    mUi->gridLayout_3->addWidget(&*mWorldCanvas);

    mPlayer.setParent(mUi->playerBox);
    mUi->formLayout_4->addWidget(&mPlayer);

    mSettingsUI->setParent(mUi->settingsBox);
    mUi->formLayout_3->addWidget(&*mSettingsUI);

    mSatchel->setParent(mUi->inventoryBox);
    mUi->gridLayout_4->addWidget(&*mSatchel);

    mWorldCanvas->show();
    mPlayer.show();
    mSatchel->show();
    mSettingsUI->show();


    loadUserData();
}

GameState::~GameState()
{
    delete mUi;
}


bool GameState::update(const sf::Time &deltaTime)
{
    return true;
}

std::string GameState::getLevelData() const
{
    std::vector<int> intData;

    std::string levelData = "";

    for (auto &levelIt : mLevelManager.getLevels())
    {
        // Process main quests first
        for (auto &questIt : levelIt->getMainQuests())
            for (auto &subQIt : questIt->getSubQuests())
                intData.push_back(subQIt->getCompletionValue());

        // Then, optional quests
        for (auto &questIt : levelIt->getOptionalQuests())
            for (auto &subQIt : questIt->getSubQuests())
                intData.push_back(subQIt->getCompletionValue());
    }

    for (auto &it = intData.rbegin(); it != intData.rend(); ++it)
        levelData.append(std::to_string(*it) + " ");

    return levelData;
}

void GameState::start()
{
    mLevelManager.getCurrentLevel().update(&*std::unique_ptr<PickUp>(new PickUp(Tiles::ID::Catnip, 1)));
    mLevelManager.getCurrentLevel().update(&*std::unique_ptr<PickUp>(new PickUp(Tiles::ID::Lavender, 1)));
    mLevelManager.getCurrentLevel().update(&*std::unique_ptr<PickUp>(new PickUp(Tiles::ID::Cattail, 3)));

    //packetData =  connection.getPacket();
    //mPlantodex.setUpPlantodex(&packetData);
}

void GameState::showPlantodex()
{
    mPlantodex.show();
}

void GameState::loadUserData()
{
    QString loadedData = getContext().connection.getPacket();

    QStringList queryList = loadedData.split(QRegExp("\\n+"), QString::SkipEmptyParts);

    QString userID;
    QString username;
    QString password;
    int currentLevel;
    int currentQuest;
    QString currentSubQuest;
    QString currentTime;
    int totalPoints;

    QStringList subQuestList;
    QStringList timeParts;
    std::vector<int> cSQ;

    //Iterates through divided list of variables, stores in array of characters
    for(int i = 0; i < queryList.size(); i++)
    {
        mUserData.userID = queryList.at(i);
        i++;
        mUserData.username = queryList.at(i);
        i++;
        mUserData.password = queryList.at(i);
        i++;
        mUserData.currentLevel = queryList.at(i).toInt();
        i++;
        mUserData.currentQuest = queryList.at(i).toInt();
        i++;

        currentSubQuest = queryList.at(i);
        i++;
        currentTime = queryList.at(i);
        i++;
        subQuestList = currentSubQuest.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        timeParts = currentTime.split(QRegExp(":+"), QString::SkipEmptyParts);

        mUserData.totalPoints = queryList.at(i).toInt();

        for(int j = 0; j < subQuestList.size(); j++)
        {
            cSQ.push_back(subQuestList.at(j).toInt());
        }

        QTime totalTime(timeParts.at(0).toInt(),timeParts.at(1).toInt(),timeParts.at(2).toInt(),0);

        mUserData.totalTime = totalTime;
        mUserData.currentSubQuest = cSQ;
    }

    //Add totalTime to a new QTime
    mTime.setHMS(timeParts.at(0).toInt(),timeParts.at(1).toInt(),timeParts.at(2).toInt(),0);
    //Start time
    mTime.start();

}

void GameState::exit()
{

    // Save to database here
   std::stringstream toSendStream;

   toSendStream << "update\n" << mUserData.userID.toStdString()
                << "\n" << mUserData.currentLevel
                << "\n" << getLevelData()
                << "\n" << mTime.hour()
                << ":"  << mTime.minute()
                << ":"  << mTime.second()
                << "\n" << mUserData.totalPoints
                << "\n";


   std::string returnString(toSendStream.str());

   getContext().connection.sendPacket(returnString);

    requestStackPop();
    requestStackPush(States::ID::LoginState);
}

// Register tiles ==============================================================================

void GameState::registerTiles()
{
    mTileManager.setTile(Tiles::ID::Grass, Properties::ID(
                         Properties::ID::Terrain | Properties::ID::Walkable | Properties::ID::Plantable));
    mTileManager.setTile(Tiles::ID::Dirt, Properties::ID(
                         Properties::ID::Terrain | Properties::ID::Walkable | Properties::ID::Plantable));
    mTileManager.setTile(Tiles::ID::DeepFreshWater, Properties::ID(
                         Properties::ID::Terrain));
    mTileManager.setTile(Tiles::ID::DeepSaltWater, Properties::ID(
                         Properties::ID::Terrain));
    mTileManager.setTile(Tiles::ID::ShallowFreshWater, Properties::ID(
                         Properties::ID::Terrain | Properties::ID::Walkable | Properties::ID::Plantable));
    mTileManager.setTile(Tiles::ID::ShallowSaltWater, Properties::ID(
                         Properties::ID::Terrain | Properties::ID::Walkable | Properties::ID::Plantable));
    mTileManager.setTile(Tiles::ID::Sand, Properties::ID(
                         Properties::ID::Terrain | Properties::ID::Walkable | Properties::ID::Plantable));
    mTileManager.setTile(Tiles::ID::RedSand, Properties::ID(
                         Properties::ID::Terrain | Properties::ID::Walkable | Properties::ID::Plantable));
    mTileManager.setTile(Tiles::ID::Mountain, Properties::ID(
                         Properties::ID::Terrain));

    mTileManager.setTile(Tiles::ID::Catnip, Properties::ID(
                         Properties::ID::Plant));
    mTileManager.setTile(Tiles::ID::Cattail, Properties::ID(
                         Properties::ID::Plant));
    mTileManager.setTile(Tiles::ID::Lavender, Properties::ID(
                         Properties::ID::Plant | Properties::ID::InsectRepellent));
}

// Register levels ==============================================================================

void GameState::registerLevels()
{
    GameContext context(mLevelManager, mTileManager, mSettings, mPlayer);

    // Create level
    LevelManager::LevelPtr level(new Level("Level 1: A New Seed", mTileManager, mLevelManager, mUi->levelContainer));
    mUi->formLayout->addWidget(&(*level));


    // Setup quests
    Level::QuestPtr quest(new Quest("So, you want to be a plant expert?", &*level));

    Quest::SubQuestPtr subQ(new SQCollectProperties("Mosquitos are pesky little creatures. Gather 15 plants to fend them off.",
                                                    Properties::ID::InsectRepellent, 0, 15, context, &*quest));

    quest->addSubQuest(std::move(subQ));



    level->addMainQuest(std::move(quest));




    quest.reset(new Quest("The Harvester", &*level));


    subQ.reset(new SQCollectSpecific("Gather 8 lavenders.",
                                     Tiles::ID::Lavender, 0, 8, context, &*quest));

    quest->addSubQuest(std::move(subQ));

    subQ.reset(new SQCollectSpecific("Gather 15 cattails.",
                                     Tiles::ID::Cattail, 0, 15, context, &*quest));

    quest->addSubQuest(std::move(subQ));

    subQ.reset(new SQCollectSpecific("Gather 7 catnips.",
                                     Tiles::ID::Catnip, 0, 7, context, &*quest));

    quest->addSubQuest(std::move(subQ));


    level->addMainQuest(std::move(quest));



    Level::RewardPtr reward(new Reward("+ 150 points", &*level));

    reward->setOnActivate([&] ()
    {
        mPlayer.addPoints(150);
    });


    level->setRewardMain(std::move(reward));




    quest.reset(new Quest("Knowledge is power", &*level));

    subQ.reset(new SQCollectType("Gather at least 3 different species of plants.", 0, 3, context, &*quest));

    quest->addSubQuest(std::move(subQ));



    level->addOptionalQuest(std::move(quest));


    reward.reset(new Reward("+ Quick Plant Analyzer \n+ 50 points", &*level));

    reward->setOnActivate([&] ()
    {
        mPlayer.addPoints(50);
    });


    level->setRewardOptional(std::move(reward));

    // Setup map
    level->getMap().setJuliaValue(std::complex<double>(-.621, 0));

    std::vector<Tiles::ID> terrainTypes{Tiles::ID::DeepFreshWater, Tiles::ID::DeepSaltWater, Tiles::ID::Dirt,
                Tiles::ID::Grass, Tiles::ID::Mountain, Tiles::ID::QuickSand, Tiles::ID::RedSand, Tiles::ID::Sand,
                Tiles::ID::ShallowFreshWater, Tiles::ID::ShallowSaltWater};

    std::vector<Tiles::ID> plantTypes{Tiles::ID::Catnip, Tiles::ID::Cattail, Tiles::ID::Lavender};

    level->setupMap(std::move(terrainTypes), std::move(plantTypes));


    // Register level into level manager
    mLevelManager.addLevel(std::move(level));


    // Level 2 ============================================


    // Create level
    level.reset(new Level("Level 2: Growing Sprout", mTileManager, mLevelManager, mUi->levelContainer));
    mUi->formLayout->addWidget(&(*level));


    // Setup quests
    quest.reset(new Quest("So, you want to be a plant expert?", &*level));

    subQ.reset(new SQCollectProperties("Mosquitos are pesky little creatures. Gather 15 plants to fend them off.",
                                       Properties::ID::InsectRepellent, 0, 15, context, &*quest));

    quest->addSubQuest(std::move(subQ));




    level->addMainQuest(std::move(quest));



    reward.reset(new Reward("+ Quick Plant Analyzer \n+ 50 points", &*level));

    reward->setOnActivate([&] ()
    {
        mPlayer.addPoints(50);
    });


    level->setRewardMain(std::move(reward));

    // Setup map
    level->getMap().setJuliaValue(std::complex<double>(-.5, .002));

    terrainTypes = std::vector<Tiles::ID>{Tiles::ID::Sand, Tiles::ID::DeepFreshWater, Tiles::ID::DeepSaltWater, Tiles::ID::Dirt,
                Tiles::ID::Grass, Tiles::ID::Mountain, Tiles::ID::QuickSand, Tiles::ID::RedSand, Tiles::ID::Sand,
                Tiles::ID::ShallowFreshWater, Tiles::ID::ShallowSaltWater};

    plantTypes = std::vector<Tiles::ID>{Tiles::ID::Catnip, Tiles::ID::Cattail, Tiles::ID::Lavender};

    level->setupMap(std::move(terrainTypes), std::move(plantTypes));


    // Register level into level manager
    mLevelManager.addLevel(std::move(level));
}
