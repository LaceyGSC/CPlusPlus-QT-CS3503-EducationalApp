#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include "Identifiers.h"

#include <unordered_map>

class TileManager
{
public:
    TileManager();

    // Adds a new type of tile with the given properties. If the
    // tile already exists, it overwrites the old properties.
    void setTile(Tiles::ID tileId, Properties::ID prop);

    // Returns Properties::ID::None if tile is not found.
    Properties::ID getTileProperties(Tiles::ID tileId) const;

    // For iterations over tiles.
    const std::unordered_map<Tiles::ID, Properties::ID, EnumClassHash>& getTiles() const;

private:
    std::unordered_map<Tiles::ID, Properties::ID, EnumClassHash> mTiles;
};

#endif // TILEMANAGER_H
