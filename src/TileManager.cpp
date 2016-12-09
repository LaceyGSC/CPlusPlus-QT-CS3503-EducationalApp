#include "TileManager.h"

TileManager::TileManager()
    : mTiles()
{
}

void TileManager::setTile(Tiles::ID tileId, Properties::ID prop)
{
    mTiles[tileId] = prop;
}

Properties::ID TileManager::getTileProperties(Tiles::ID tileId) const
{
    auto finder = mTiles.find(tileId);
    if (finder != mTiles.end())
        return finder->second;

    return Properties::ID::None;
}

const std::unordered_map<Tiles::ID, Properties::ID, EnumClassHash>& TileManager::getTiles() const
{
    return mTiles;
}
