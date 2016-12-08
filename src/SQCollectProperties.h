#ifndef SQCOLLECTPROPERTIES_H
#define SQCOLLECTPROPERTIES_H

#include <QLabel>
#include <QProgressBar>

#include "SubQuest.h"

#include <vector>
#include <memory>

// This is a type of quest (collection quest)
class SQCollectProperties : public SubQuest
{
public:
    SQCollectProperties(const QString &desc, Plant::Properties prop, int actual, QWidget *parent = 0);

    virtual void update(Command *command);

private:

    Plant::Properties mProp;

    int mActual;
    int mCollected;
};

#endif // SQCOLLECTPROPERTIES_H
