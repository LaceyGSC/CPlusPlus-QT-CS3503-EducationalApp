#ifndef LEVEL_H
#define LEVEL_H

#include <QWidget>
#include <Qstring>

#include "Quest.h"
#include "Commands.h"
#include "Reward.h"

#include <vector>
#include <memory>

class LevelManager;

namespace Ui {
    class Level;
}

class Level : public QWidget
{
    Q_OBJECT
public:
    typedef std::unique_ptr<Quest> QuestPtr;
    typedef std::unique_ptr<Reward> RewardPtr;

public:
    explicit Level(const QString &name, LevelManager& parentManager, QWidget *parent = 0);
    ~Level();

    const QString& getName() const;

    void addMainQuest(QuestPtr quest);
    void addOptionalQuest(QuestPtr quest);

    void setRewardMain(RewardPtr reward);
    void setRewardOptional(RewardPtr reward);

    bool isMainCompleted() const;
    bool isOptionalCompleted() const;

    void update(Command *command);

public slots:
    void getNextLevel();
    void getPrevLevel();

private:
    Ui::Level *mUi;

    QString mLevelName;

    LevelManager *mParentManager;

    //std::map<QuestPtr, RewardPtr> mMainQuests;
    //std::map<QuestPtr, RewardPtr> mOptionalQuests;

    std::vector<QuestPtr> mMainQuests;
    std::vector<QuestPtr> mOptionalQuests;

    RewardPtr mMainReward;
    RewardPtr mOptionalReward;
};

#endif // LEVEL_H
