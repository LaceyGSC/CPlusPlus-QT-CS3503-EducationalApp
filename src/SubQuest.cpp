#include "SubQuest.h"

#include "Quest.h"

#include <utility>

SubQuest::SubQuest(GameState::GameContext gameContext, QWidget *parent)
    : QWidget(parent)
    , mCompleted(false)
    , mGameContext(gameContext)
    , mDesc(this)
    , mBar(this)
{
    show();
}

QGridLayout* SubQuest::getLayout() const
{
    return dynamic_cast<Quest*>(parent())->getLayout();
}

bool SubQuest::isCompleted() const
{
    return mCompleted;
}
