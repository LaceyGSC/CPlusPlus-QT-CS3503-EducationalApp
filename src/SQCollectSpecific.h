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
    struct Data
    {
        Data(const QString &desc, Plant::ID id, int actual);

        Plant::ID id;

        int actual;
        int collected;

        QLabel desc;
        QProgressBar bar;
    };

public:
    typedef std::unique_ptr<SQCollectSpecific::Data> DataPtr;

public:
    SQCollectSpecific(SQCollectSpecific::DataPtr data, QWidget *parent = 0);

    virtual void update(Command *command);

private:
    SQCollectSpecific::DataPtr mData;
};

#endif // SQCOLLECTSPECIFIC_H
