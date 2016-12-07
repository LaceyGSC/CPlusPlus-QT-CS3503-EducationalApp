#ifndef COLLECTIONQ_H
#define COLLECTIONQ_H

#include <QProgressBar>
#include <QLabel>
#include <QGridLayout>

#include "Quest.h"
#include "Commands.h"

#include <map>
#include <memory>

// This is a type of quest (collection quest)
class CollectionQ : public Quest
{
public:
    struct Data
    {
        Data(int actual, QGridLayout *containerLayout, QWidget *parent = 0);

        int actual;
        int collected;

        QProgressBar bar;
        QLabel desc;
    };

public:
    typedef std::unique_ptr<CollectionQ::Data> Ptr;

public:
    CollectionQ(const QString &title, const QString &description, QWidget *parent = 0);

    void addData(Plant::ID id, CollectionQ::Ptr data);

    virtual void update(Command command);

private:
    std::map<Plant::ID, CollectionQ::Ptr> mCollectionData;
    //std::map<Plant::ID, int> mActualData;
};

#endif // COLLECTIONQ_H
