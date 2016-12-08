#include "Level.h"
#include "ui_Level.h"

#include "Quest.h"

#include <utility>

Level::Level(QWidget *parent)
    : QWidget(parent)
    , mUi(new Ui::Level)
    , mQuests()
    , mCompletedQuests(0)
{
    mUi->setupUi(this);

    show();
}

Level::~Level()
{
    delete mUi;
}

void Level::addQuest(std::unique_ptr<Quest> quest)
{
    mUi->formLayout->addWidget(&(*quest));
    mQuests.push_back(std::move(quest));
}

void Level::addCompletedQuest()
{
    ++mCompletedQuests;
}

bool Level::isCompleted() const
{
    return mCompletedQuests == mQuests.size();
}

void Level::update(Command *command)
{
    for (auto &it : mQuests)
        it->update(command);
}
