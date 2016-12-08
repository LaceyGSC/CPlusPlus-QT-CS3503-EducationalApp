#include "Level.h"
#include "ui_Level.h"

#include "Quest.h"
#include "LevelManager.h"

#include <utility>

Level::Level(const QString &name, LevelManager& parentManager, QWidget *parent)
    : QWidget(parent)
    , mLevelName(name)
    , mParentManager(&parentManager)
    , mUi(new Ui::Level)
    , mMainQuests()
    , mOptionalQuests()
    , mMainReward(nullptr)
    , mOptionalReward(nullptr)
{
    mUi->setupUi(this);

    mUi->titleLabel->setText(name);

    mUi->prevLevel->hide();
    mUi->nextLevel->hide();

    connect(mUi->prevLevel, SIGNAL(pressed()), this, SLOT(getPrevLevel()));
    connect(mUi->nextLevel, SIGNAL(pressed()), this, SLOT(getNextLevel()));
}

Level::~Level()
{
    delete mUi;
}

const QString& Level::getName() const
{
    return mLevelName;
}

void Level::addMainQuest(Level::QuestPtr quest)
{
    mUi->formLayout_2->addWidget(&*quest);
    quest->setHashId(mMainQuests.size());

    //mMainQuests.insert(std::make_pair(std::move(quest), std::move(reward)));
    mMainQuests.push_back(std::move(quest));
}

void Level::addOptionalQuest(Level::QuestPtr quest)
{
    mUi->formLayout_3->addWidget(&*quest);
    quest->setHashId(mOptionalQuests.size());

    //mMainQuests.insert(std::make_pair(std::move(quest), std::move(reward)));
    mOptionalQuests.push_back(std::move(quest));
}

void Level::setRewardMain(RewardPtr reward)
{
    mUi->formLayout->addWidget(&*reward);

    mMainReward = std::move(reward);
}

void Level::setRewardOptional(RewardPtr reward)
{
    mUi->formLayout_4->addWidget(&*reward);

    mOptionalReward = std::move(reward);
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

    if (isMainCompleted())
    {
        if (mMainReward != nullptr)
            mMainReward->activate();
        mUi->nextLevel->show();
        mUi->prevLevel->show();
    }

    for (auto &it : mOptionalQuests)
        it->update(command);

    if (isOptionalCompleted())
        if (mOptionalReward != nullptr)
            mOptionalReward->activate();
}

void Level::getNextLevel()
{
    mParentManager->nextLevel();
}

void Level::getPrevLevel()
{
    mParentManager->prevLevel();
}
