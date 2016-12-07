#ifndef LEVEL_H
#define LEVEL_H

#include <QWidget>

#include "Quest.h"
#include "Commands.h"

#include <vector>
#include <memory>

namespace Ui {
    class Level;
}

class Level : public QWidget
{
    Q_OBJECT

public:
    explicit Level(QWidget *parent = 0);
    ~Level();

    void addQuest(std::unique_ptr<Quest> quest);

    void addCompletedQuest();

    bool isCompleted() const;

    void update(Command command);

public:
    Ui::Level *mUi;

    std::vector<std::unique_ptr<Quest>> mQuests;

    int mCompletedQuests;
};

#endif // LEVEL_H
