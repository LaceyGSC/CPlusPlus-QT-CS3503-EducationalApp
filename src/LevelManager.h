#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "Level.h"

#include <vector>
#include <memory>

class LevelManager
{
public:
    typedef std::unique_ptr<Level> LevelPtr;

public:
    LevelManager();

    void addLevel(LevelManager::LevelPtr level);

    bool prevLevel();
    bool nextLevel();

    Level& getCurrentLevel() const;

    int getNumberOfLevels() const;

    Level& getFirstLevel() const;

private:
    std::vector<LevelManager::LevelPtr>  mLevels;
    int mCurrentLevel;

};

#endif // LEVELMANAGER_H
