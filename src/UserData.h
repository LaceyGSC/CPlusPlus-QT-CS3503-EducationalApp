#ifndef USERDATA_H
#define USERDATA_H

#include <QString>
#include <QTime>
#include <vector>


struct UserData
{
    UserData();
    UserData(QString id, QString u, QString p, int cL, int cQ, std::vector<int> cS, QTime tT, int tP);
    QString userID;
    QString username;
    QString password;
    QTime totalTime;
    int currentLevel;
    int currentQuest;
    int totalPoints;
    std::vector<int> currentSubQuest;
};

#endif // CHARACTER_H
