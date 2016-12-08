#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>


class Character
{
public:
    Character();
    Character(QString id, QString u, QString p, int cL, int cQ, int cP);
    QString userID;
    QString username;
    QString password;
    int currentLevel;
    int currentQuest;
    int currentProgress;
};

#endif // CHARACTER_H
