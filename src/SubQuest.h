#ifndef SUBQUEST_H
#define SUBQUEST_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QProgressBar>

#include "Commands.h"

class Quest;

// This is a type of quest (collection quest)
class SubQuest : public QWidget
{
public:
    // Parent should be of type Quest
    SubQuest(QWidget *parent = 0);

    //void addData(SubQuest::Ptr data);

    QGridLayout* getLayout() const;

    bool isCompleted() const;

    virtual void update(Command *command) = 0;

protected:
    bool mCompleted;

    QLabel mDesc;
    QProgressBar mBar;
};

#endif // SUBQUEST_H
