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
    struct Data
    {
        Data(const QString &desc, Plant::Properties prop, int actual);

        Plant::Properties prop;

        int actual;
        int collected;

        QLabel desc;
        QProgressBar bar;
    };

public:
    typedef std::unique_ptr<SQCollectProperties::Data> DataPtr;

public:
    SQCollectProperties(SQCollectProperties::DataPtr data, QWidget *parent = 0);

    virtual void update(Command *command);

private:
    SQCollectProperties::DataPtr mData;
};

#endif // SQCOLLECTPROPERTIES_H
