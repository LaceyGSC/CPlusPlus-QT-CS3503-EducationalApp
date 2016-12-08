#ifndef LEVEL_H
#define LEVEL_H

#include <QWidget>
#include <Qstring>

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
    explicit Level(const QString &name, QWidget *parent = 0);
    ~Level();

    const QString& getName() const;

    void addMainQuest(std::unique_ptr<Quest> quest);
    void addOptionalQuest(std::unique_ptr<Quest> quest);

    bool isMainCompleted() const;
    bool isOptionalCompleted() const;

    void update(Command *command);

public:
    Ui::Level *mUi;

    QString mLevelName;

    std::vector<std::unique_ptr<Quest>> mMainQuests;
    std::vector<std::unique_ptr<Quest>> mOptionalQuests;
};

#endif // LEVEL_H
