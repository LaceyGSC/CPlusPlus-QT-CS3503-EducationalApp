#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QTimer>

#include "Identifiers.h"

#include <complex>

namespace Ui {
class Player;
}

class Player : public QWidget
{
    Q_OBJECT

public:
    explicit Player(QWidget *parent = 0);
    ~Player();

    void turn(Directions::ID facing);
    Directions::ID getFacing() const;

    void addPoints(int points);

    int getPoints() const;

private slots:
    void endAnimation();

private:
    Ui::Player *mUi;

    Directions::ID mFacing;

    // For animation
    QTimer mTimer;

    int mPendingPoints;
    int mPoints;
};

#endif // PLAYER_H
