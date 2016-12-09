#ifndef SQCOLLECTTYPE_H
#define SQCOLLECTTYPE_H

#include <QLabel>
#include <QProgressBar>

#include "SubQuest.h"

#include <vector>
#include <memory>
#include <unordered_set>

// This is a type of quest (collection quest)
class SQCollectType : public SubQuest
{
public:
    SQCollectType(const QString &desc, int actualTypes, GameState::GameContext gameContext, QWidget *parent = 0);

    virtual void update(Command *command);

private:
    std::unordered_set<Tiles::ID, EnumClassHash> mCollectedTypes;

    int mActualTypes;
};

#endif // SQCOLLECTTYPE_H
