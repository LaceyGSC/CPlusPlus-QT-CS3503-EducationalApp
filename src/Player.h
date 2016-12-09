#ifndef PLAYER_H
#define PLAYER_H

#include "Identifiers.h"

#include <complex>

class Player
{
public:
    Player();

    void turn(Directions::ID facing);

    Directions::ID getFacing() const;

private:
    Directions::ID mFacing;
};

#endif // PLAYER_H
