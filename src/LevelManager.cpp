#include "LevelManager.h"

#include <cassert>

LevelManager::LevelManager()
    : mLevels()
    , mCurrentLevel(0)
{
}

void LevelManager::addLevel(LevelManager::LevelPtr level)
{
    level->hide();
    mLevels.push_back(std::move(level));
}

bool LevelManager::prevLevel()
{
    if (mCurrentLevel == 0 || mLevels.size() == 0)
        return false;

    mLevels.at(mCurrentLevel)->hide();
    --mCurrentLevel;
    mLevels.at(mCurrentLevel)->show();
    return true;
}

bool LevelManager::nextLevel()
{
    if (mCurrentLevel == mLevels.size() - 1 || mLevels.size() == 0)
        return false;

    if (mLevels.at(mCurrentLevel)->isHidden())
        mLevels.at(mCurrentLevel)->show();
    else
    {
        mLevels.at(mCurrentLevel)->hide();
        ++mCurrentLevel;
        mLevels.at(mCurrentLevel)->show();
    }

    return true;
}

Level& LevelManager::getCurrentLevel() const
{
    assert(mCurrentLevel < mLevels.size());
    return *(mLevels.at(mCurrentLevel));
}
