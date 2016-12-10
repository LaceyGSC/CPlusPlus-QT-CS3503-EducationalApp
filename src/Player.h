#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>

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

private:
    Ui::Player *mUi;

    Directions::ID mFacing;
};

#endif // PLAYER_H
