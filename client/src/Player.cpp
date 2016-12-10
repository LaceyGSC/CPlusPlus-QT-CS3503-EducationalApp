#include "Player.h"
#include "ui_Player.h"

#include <QString>
#include <QTextEdit>

Player::Player(QWidget *parent)
    : QWidget(parent)
    , mUi(new Ui::Player)
    , mFacing(Directions::ID::Down)
    , mTimer()
    , mPendingPoints(0)
    , mPoints(0)
{
    mUi->setupUi(this);

    mUi->pointsField->setText(QString::number(0));
    mUi->pointsField->setAlignment(Qt::AlignCenter);

    mTimer.setInterval(3000);
    mTimer.setSingleShot(true);

    QObject::connect(&mTimer, SIGNAL(timeout()), this, SLOT(endAnimation()));
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

void Player::addPoints(int points)
{
    mPendingPoints += points;

    QString string = "<font color=\"#33cc33\"> +" + QString::number(mPendingPoints) + "</font>";

    mPoints += points;
    mUi->pointsField->setHtml(QString::number(mPoints - mPendingPoints) + string);
    mUi->pointsField->setAlignment(Qt::AlignCenter);

    mTimer.start();
}

int Player::getPoints() const
{
    return mPoints;
}

void Player::endAnimation()
{
    mUi->pointsField->setText(QString::number(mPoints));
    mUi->pointsField->setAlignment(Qt::AlignCenter);

    mPendingPoints = 0;
}
