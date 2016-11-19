#include "mysqlconnection.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

MySQLConnection::MySQLConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("plantquestdb.ck8fat1uoilr.us-west-2.rds.amazonaws.com");
    db.setPort(3306);
    db.setDatabaseName("PlantQuestDB");
    db.setUserName("plantadmin");
    db.setPassword("plantpassword");

    bool ok = db.open();
     qDebug() << ok;

    QSqlQuery query;
    query.exec("Select * from PlantTable");

    while (query.next())
    {
            int plantIndex = query.value(0).toInt();
            QString name = query.value(1).toString();
            qDebug() << plantIndex << name;
    }

}
