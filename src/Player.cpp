#include "Player.h"
#include "ui_Player.h"

Player::Player(QWidget *parent)
    : QWidget(parent)
    , mUi(new Ui::Player)
    , mFacing(Directions::ID::Down)
{
    mUi->setupUi(this);
}

Player::~Player()
{
    delete mUi;
}

void Player::turn(Directions::ID facing)
{
    mFacing = facing;
}

Directions::ID Player::getFacing() const
{
    return mFacing;
}
