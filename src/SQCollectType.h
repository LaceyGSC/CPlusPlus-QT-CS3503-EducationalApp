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
    struct Data
    {
        Data(const QString &desc, int actualTypes);

        std::unordered_set<Plant::ID> collectedTypes;

        int actualTypes;

        QLabel desc;
        QProgressBar bar;
    };

public:
    typedef std::unique_ptr<SQCollectType::Data> DataPtr;

public:
    SQCollectType(SQCollectType::DataPtr data, QWidget *parent = 0);

    virtual void update(Command *command);

private:
    SQCollectType::DataPtr mData;
};

#endif // SQCOLLECTTYPE_H
