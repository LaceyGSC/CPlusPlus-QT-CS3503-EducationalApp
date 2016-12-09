#include "Character.h"

Character::Character()
{

}

Character::Character(QString id, QString u, QString p, int cL, int cQ, std::vector<int> cS, std::vector<int> cP, QTime tT)
{
    userID = id;
    username = u;
    password = p;
    currentLevel = cL;
    currentQuest = cQ;
    currentSubQuest = cS;
    currentProgress = cP;
    totalTime = tT;
}
