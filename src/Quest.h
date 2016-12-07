#ifndef QUEST_H
#define QUEST_H

#include <QWidget>
#include <QString>

#include "Commands.h"

namespace Ui {
class Quest;
}

class Quest : public QWidget
{
    Q_OBJECT

public:
    // The parent should be of type Level
    explicit Quest(const QString &title, const QString &description, QWidget *parent = 0);
    ~Quest();

    virtual void update(Command command) = 0;

//protected:
    // val goes from 0 to 100
    void setCompletion(int val);
    int getCompletion() const;

    // void update(const Plant &pickedPlant);

protected:
    Ui::Quest *mUi;
};

#endif // QUEST_H
