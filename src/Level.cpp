#include "Level.h"
#include "ui_Level.h"

#include "Quest.h"
#include "LevelManager.h"

#include <utility>

Level::Level(const QString &name, TileManager &tileManager, LevelManager &parentManager, QWidget *parent)
    : QWidget(parent)
    , mUi(new Ui::Level)
    , mTileManager(&tileManager)
    , mParentManager(&parentManager)
    , mMainQuests()
    , mOptionalQuests()
    , mMainReward(nullptr)
    , mOptionalReward(nullptr)
    , mMap()
    , mTerrainTypes()
    , mPlantTypes()
    , mPlayerPosition(0, 0)
    , mPickedPlants()
{
    mMap.setRefSize(512);

    mUi->setupUi(this);

    mUi->titleLabel->setText(name);

    if (mParentManager->getNumberOfLevels() == 0)
        mUi->prevLevel->hide();
    else
        mUi->prevLevel->show();

    mUi->nextLevel->hide();
    mUi->main->hide();
    mUi->optional->hide();
    mUi->rewardMain->hide();
    mUi->rewardOptional->hide();

    connect(mUi->prevLevel, SIGNAL(pressed()), this, SLOT(getPrevLevel()));
    connect(mUi->nextLevel, SIGNAL(pressed()), this, SLOT(getNextLevel()));
}

Level::~Level()
{
    delete mUi;
}

void Level::addMainQuest(Level::QuestPtr quest)
{
    if (mUi->main->isHidden())
        mUi->main->show();

    mUi->formLayout_2->addWidget(&*quest);
    quest->setHashId(mMainQuests.size());

    mMainQuests.push_back(std::move(quest));
}

void Level::addOptionalQuest(Level::QuestPtr quest)
{
    if (mUi->optional->isHidden())
        mUi->optional->show();

    mUi->formLayout_3->addWidget(&*quest);
    quest->setHashId(mOptionalQuests.size());

    mOptionalQuests.push_back(std::move(quest));
}

void Level::setRewardMain(RewardPtr reward)
{
    if (mUi->rewardMain->isHidden())
        mUi->rewardMain->show();

    mUi->formLayout->addWidget(&*reward);

    mMainReward = std::move(reward);
}

void Level::setRewardOptional(RewardPtr reward)
{
    if (mUi->rewardOptional->isHidden())
        mUi->rewardOptional->show();

    mUi->formLayout_4->addWidget(&*reward);

    mOptionalReward = std::move(reward);
}

void Level::giveRewardMain()
{
    if (isMainCompleted())
    {
        if (mMainReward != nullptr)
            mMainReward->activate();
        mUi->nextLevel->show();
    }
}

void Level::giveRewardOptional()
{
    if (isOptionalCompleted())
    {
        if (mOptionalReward != nullptr)
            mOptionalReward->activate();
    }
}

bool Level::isMainCompleted() const
{
    if (mMainQuests.empty())
        return false;

    for (auto &it : mMainQuests)
        if (!it->isCompleted())
            return false;

    return true;
}

bool Level::isOptionalCompleted() const
{
    if (mOptionalQuests.empty())
        return false;

    for (auto &it : mOptionalQuests)
        if (!it->isCompleted())
            return false;

    return true;
}

void Level::update(Command *command)
{
    for (auto &it : mMainQuests)
        it->update(command);

    giveRewardMain();

    for (auto &it : mOptionalQuests)
        it->update(command);

    giveRewardOptional();
}

FractalExpressionEvaluator& Level::getMap()
{
    return mMap;
}

void Level::setupMap(const std::vector<Tiles::ID> &terrainIds, const std::vector<Tiles::ID> &plantIds)
{
    for (auto &it : terrainIds)
        if (mTileManager->getTileProperties(it) & Properties::ID::Terrain)
            mTerrainTypes.push_back(it);

    for (auto &it : plantIds)
        if (mTileManager->getTileProperties(it) & Properties::ID::Plant)
            mPlantTypes.push_back(it);
}

const std::vector<Tiles::ID>& Level::getTerrainTypes() const
{
    return mTerrainTypes;
}

const std::vector<Tiles::ID>& Level::getPlantTypes() const
{
    return mPlantTypes;
}

void Level::setPlayerPosition(const std::complex<int> &position)
{
    mPlayerPosition = position;
}

void Level::movePlayer(const std::complex<int> &vector)
{
    mPlayerPosition += vector;
}

std::complex<int> Level::getPlayerPosition() const
{
    return mPlayerPosition;
}

void Level::addPickedPlant(const std::complex<int> &position)
{
    mPickedPlants.insert(position);
}

bool Level::isPlantPicked(const std::complex<int> &position) const
{
    return mPickedPlants.find(position) != mPickedPlants.end();
}

void Level::getNextLevel()
{
    mParentManager->nextLevel();
}

void Level::getPrevLevel()
{
    mParentManager->prevLevel();
}
