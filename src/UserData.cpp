#include "UserData.h"

UserData::UserData()
{

}

UserData::UserData(QString id, QString u, QString p, int cL, int cQ, std::vector<int> cS, QTime tT, int tP)
{
    userID = id;
    username = u;
    password = p;
    currentLevel = cL;
    currentQuest = cQ;
    currentSubQuest = cS;
    totalTime = tT;
    totalPoints = tP;
}
