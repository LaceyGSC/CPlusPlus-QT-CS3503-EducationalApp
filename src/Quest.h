#ifndef QUEST_H
#define QUEST_H

#include <QWidget>
#include <QString>
#include <QGridLayout>

#include "Commands.h"
#include "SubQuest.h"

#include <vector>
#include <memory>

namespace Ui {
class Quest;
}

class Quest : public QWidget
{
    Q_OBJECT
public:
    typedef std::unique_ptr<SubQuest> SubQuestPtr;

public:
    // The parent should be of type Level
    explicit Quest(const QString &title, QWidget *parent = 0);
    ~Quest();

    void addSubQuest(SubQuestPtr subQuest);

    void update(Command *command);

    QGridLayout* getLayout() const;

    bool isCompleted() const;

private:
    Ui::Quest *mUi;

    std::vector<Quest::SubQuestPtr> mSubQuests;
};

#endif // QUEST_H
