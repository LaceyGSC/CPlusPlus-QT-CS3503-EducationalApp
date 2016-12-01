#include "MySQLConnection.h"

#include <iostream>

MySQLConnection::MySQLConnection()
{
    // Create connection and initialize necessary information
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("plantquestdb.ck8fat1uoilr.us-west-2.rds.amazonaws.com");
    db.setPort(3306);
    db.setDatabaseName("PlantQuestDB");
    db.setUserName("plantadmin");
    db.setPassword("plantpassword");
    db.open();

    // Query the database
    QSqlTableModel model; // Automatically connects to the default database.
    model.setTable("PlantTable");
    model.select();

    // Save information from query
    for(int i = 0; i < model.rowCount(); ++i)
    {
        QString name = model.record(i).value("name").toString();
        QString latinName = model.record(i).value("latinname").toString();
        QString description = model.record(i).value("description").toString();
        QString uses = model.record(i).value("uses").toString();
        QString location = model.record(i).value("location").toString();

        std::cout << name.toStdString() << std::endl;
        std::cout << latinName.toStdString() << std::endl;
        std::cout << description.toStdString() << std::endl;
        std::cout << uses.toStdString() << std::endl;
        std::cout << location.toStdString() << std::endl << std::endl;
    }

    // Close the database connection
    db.close();
    db.removeDatabase(db.databaseName());
}
