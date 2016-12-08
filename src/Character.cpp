#include "Character.h"

Character::Character()
{

}

Character::Character(QString id, QString u, QString p, int cL, int cQ, int cP)
{
    userID = id;
    username = u;
    password = p;
    currentLevel = cL;
    currentQuest = cQ;
    currentProgress = cP;
}
