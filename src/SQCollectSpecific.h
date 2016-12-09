#ifndef SQCOLLECTSPECIFIC_H
#define SQCOLLECTSPECIFIC_H

#include <QLabel>
#include <QProgressBar>

#include "SubQuest.h"

#include <vector>
#include <memory>

// This is a type of quest (collection quest)
class SQCollectSpecific : public SubQuest
{
public:
    SQCollectSpecific(const QString &desc, Tiles::ID id, int collected, int actual, GameState::GameContext gameContext, QWidget *parent = 0);

    virtual void update(Command *command);

private:

    Tiles::ID mId;

    int mActual;
    int mCollected;
};

#endif // SQCOLLECTSPECIFIC_H
