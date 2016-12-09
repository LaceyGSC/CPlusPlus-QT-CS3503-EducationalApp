#ifndef LEVEL_H
#define LEVEL_H

#include <QWidget>
#include <Qstring>

#include "SFML/Graphics.hpp"

#include "Quest.h"
#include "Commands.h"
#include "Reward.h"
#include "FractalExpressionEvaluator.h"
#include "TileManager.h"

#include <vector>
#include <memory>
#include <unordered_set>

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
    explicit Level(const QString &name, TileManager &tileManager, LevelManager &parentManager, QWidget *parent = 0);
    ~Level();

    void addMainQuest(QuestPtr quest);
    void addOptionalQuest(QuestPtr quest);

    void setRewardMain(RewardPtr reward);
    void setRewardOptional(RewardPtr reward);

    bool isMainCompleted() const;
    bool isOptionalCompleted() const;

    void update(Command *command);

    FractalExpressionEvaluator& getMap();

    // Only adds tiles that have Properties::ID::Terrain and Properties::ID::Plant
    // respectively. The rest will be ignored.
    void setupMap(const std::vector<Tiles::ID> &terrainIds, const std::vector<Tiles::ID> &plantIds);

    const std::vector<Tiles::ID>& getTerrainTypes() const;
    const std::vector<Tiles::ID>& getPlantTypes() const;

    void setPlayerPosition(const std::complex<int> &position);
    void movePlayer(const std::complex<int> &vector);
    std::complex<int> getPlayerPosition() const;

    void addPickedPlant(const std::complex<int> &position);
    bool isPlantPicked(const std::complex<int> &position) const;

public slots:
    void getNextLevel();
    void getPrevLevel();

private:
    Ui::Level *mUi;

    TileManager *mTileManager;
    LevelManager *mParentManager;

    std::vector<QuestPtr> mMainQuests;
    std::vector<QuestPtr> mOptionalQuests;

    RewardPtr mMainReward;
    RewardPtr mOptionalReward;

    FractalExpressionEvaluator mMap;

    std::vector<Tiles::ID> mTerrainTypes;
    std::vector<Tiles::ID> mPlantTypes;

    std::complex<int> mPlayerPosition;

    std::unordered_set<std::complex<int>, IntComplexHash> mPickedPlants;
};

#endif // LEVEL_H
