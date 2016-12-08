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
    SQCollectSpecific(const QString &desc, Plant::ID id, int actual, QWidget *parent = 0);

    virtual void update(Command *command);

private:

    Plant::ID mId;

    int mActual;
    int mCollected;
};

#endif // SQCOLLECTSPECIFIC_H
