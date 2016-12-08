#include "Level.h"
#include "ui_Level.h"

#include "Quest.h"

#include <utility>

Level::Level(const QString &name, QWidget *parent)
    : QWidget(parent)
    , mLevelName(name)
    , mUi(new Ui::Level)
    , mMainQuests()
    , mOptionalQuests()
{
    mUi->setupUi(this);
}

Level::~Level()
{
    delete mUi;
}

const QString& Level::getName() const
{
    return mLevelName;
}

void Level::addMainQuest(std::unique_ptr<Quest> quest)
{
    mUi->formLayout_2->addWidget(&(*quest));
    mMainQuests.push_back(std::move(quest));
}

void Level::addOptionalQuest(std::unique_ptr<Quest> quest)
{
    mUi->formLayout_3->addWidget(&(*quest));
    mOptionalQuests.push_back(std::move(quest));
}

bool Level::isMainCompleted() const
{
    for (auto &it : mMainQuests)
        if (!it->isCompleted())
            return false;

    return true;
}

bool Level::isOptionalCompleted() const
{
    for (auto &it : mOptionalQuests)
        if (!it->isCompleted())
            return false;

    return true;
}

void Level::update(Command *command)
{
    for (auto &it : mMainQuests)
        it->update(command);
    for (auto &it : mOptionalQuests)
        it->update(command);
}
