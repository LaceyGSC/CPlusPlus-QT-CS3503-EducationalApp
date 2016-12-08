#include "Quest.h"
#include "ui_Quest.h"

#include "Level.h"

#include <utility>

Quest::Quest(const QString &title, QWidget *parent)
    : QWidget(parent)
    , mUi(new Ui::Quest)
{
    mUi->setupUi(this);

    // Setup columns for quest description (column 0) and bar (column 1)
    mUi->gridLayout->setColumnStretch(0, 1);
    mUi->gridLayout->setColumnStretch(1, 1);

    mUi->title->setText(title);

    show();
}

Quest::~Quest()
{
    delete mUi;
}

void Quest::addSubQuest(SubQuestPtr subQuest)
{
    mSubQuests.push_back(std::move(subQuest));
}

void Quest::update(Command *command)
{
    for (auto &it : mSubQuests)
        it->update(command);
}

QGridLayout* Quest::getLayout() const
{
    return mUi->gridLayout;
}

bool Quest::isCompleted() const
{
    for (auto &it : mSubQuests)
        if (!it->isCompleted())
            return false;

    return true;
}
