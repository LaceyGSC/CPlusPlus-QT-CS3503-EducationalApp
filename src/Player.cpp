#include "Player.h"

Player::Player()
    : mFacing(Directions::ID::Down)
{
}
void Player::turn(Directions::ID facing)
{
    mFacing = facing;
}

Directions::ID Player::getFacing() const
{
    return mFacing;
}
