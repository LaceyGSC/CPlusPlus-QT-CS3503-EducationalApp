#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlError>
#include <sstream>
#include <iostream>
#include <fstream>
#include <QDesktopServices>
#include <QUrl>
#include <QStringList>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connected = false;

    // The TCP socket should be non-blocking to keep the GUI from hanging
    client.setBlocking(false);
    listener.listen(53001);

}

MainWindow::~MainWindow()
{
    delete ui;
    client.disconnect();
}

void MainWindow::setupConnection()
{
    std::cout << "Waiting for client" << std::endl;
    listener.accept(client);
    std::cout << "Connected to client" << std::endl;

    // Start checking for packets
    QTimer::singleShot(100, this, SLOT(getPackets()));

    connectToDatabase();

}

void MainWindow::closeConnection()
{
    std::cout << "Disconnecting " << std::endl;
    client.disconnect();

}

void MainWindow::getPackets()
{
    sf::Packet packet;
    QApplication::flush();

    if (client.receive(packet) == sf::Socket::Done)
    {
        // The client has sent some data, we can receive it
        std::string msg;
        packet >> msg;
        qDebug() << "Msg received: " << msg.c_str() << "\n";
        recievedQuery = QString::fromStdString(msg);

        QStringList queryList = recievedQuery.split(QRegExp("\\s+"), QString::SkipEmptyParts);

        if(queryList.at(0) == "login")
        {
                queryDatabaseUserLogin(queryList.at(1),queryList.at(2));
        }
        else if(queryList.at(0) == "create")
        {
                queryDatabaseUserCreate(queryList.at(1),queryList.at(2));
        }
        else if(queryList.at(0) == "delete")
        {
                queryDatabaseUserDelete(queryList.at(1));
        }
        else if (queryList.at(0) == "plant")
        {
                queryDatabasePlant();
        }
        else if(queryList.at(0) == "webpage")
        {
                createWebPage();
        }
    }
    // Use a timer to keep checking for packets while keeping the GUI alive
    QTimer::singleShot(100, this, SLOT(getPackets()));

}

void MainWindow::connectToDatabase()
{
    //Connects to the plant database
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("plantquestdb.ck8fat1uoilr.us-west-2.rds.amazonaws.com");
    db.setPort(3306);
    db.setDatabaseName("PlantQuestDB");
    db.setUserName("plantadmin");
    db.setPassword("plantpassword");
    qDebug() << db.open();

}

void MainWindow::queryDatabasePlant()
{
    sf::Packet packet;
    std::stringstream packetStream;
    const char* returnChars;
    QSqlQuery query(db);

    QString theQuery = "Select * from PlantTable";

    //Executes the query recieved from the client for plant data
    query.exec(theQuery);

    while (query.next())
    {
        //Gets plant index info
        QString name = query.value(1).toString();
        QString latinName = query.value(2).toString();
        QString description = query.value(3).toString();
        QString uses = query.value(4).toString();
        QString location = query.value(5).toString();

        //Adds all plant info to stringstream
        packetStream << name.toStdString() <<"\n"
                     << latinName.toStdString() << "\n"
                     << description.toStdString() << "\n"
                     << uses.toStdString() << "\n"
                     << location.toStdString() << "\n";
    }

    //Creates string from stringstream, needed to get const char*
    std::string returnString(packetStream.str());
    //Creates const char* to add into returning packet
    returnChars = returnString.c_str();

    packet << returnChars;
    client.send(packet);

//    packet << returnChars;
//   client.send(packet);

}

void MainWindow::queryDatabaseUserLogin(QString name, QString password)
{
    sf::Packet packet;
    std::stringstream packetStream;
    const char* returnChars;
    QSqlQuery query(db);

    QString theQuery = "Select * from Users where username = \"" + name + "\" and password = \"" + password +"\"";

     //Executes the query recieved from the client for user data
    query.exec(theQuery);

   packet.clear();

    if(query.size() != 1)
    {
        //send back failure number
            packet << "0";

            client.send(packet);
    }
    else
    {
        //test for admin, send back admin number if successful and name matches
        if(name == "Admin")
        {
            packet << "2";

            client.send(packet);

            packet.clear();

            //for admin, send back all user data for management

            theQuery = "Select * from Users";

            query.exec(theQuery);

            while (query.next())
            {
                int userID = query.value(0).toInt();
                QString username = query.value(1).toString();
                QString pass = query.value(2).toString();
                int currentLevel = query.value(3).toInt();
                int currentQuest = query.value(4).toInt();
                int currentProgress = query.value(6).toInt();

                packetStream << userID <<"\n"
                             << username.toStdString() << "\n"
                             << pass.toStdString() << "\n"
                             << currentLevel << "\n"
                             << currentQuest << "\n"
                             << currentProgress << "\n";

            }

            //Creates string from stringstream, needed to get const char*
            std::string returnString(packetStream.str());
            //Creates const char* to add into returning packet
            returnChars = returnString.c_str();

            packet << returnChars;
            client.send(packet);

        }
        else
        {
            //send back number for single success, non admin
            packet << "1";
            client.send(packet);

            packet.clear();

            //send back user data
            while (query.next())
            {
                int userID = query.value(0).toInt();
                QString username = query.value(1).toString();
                int currentLevel = query.value(3).toInt();
                int currentQuest = query.value(4).toInt();
                int currentProgress = query.value(6).toInt();

                packetStream << userID <<"\n"
                             << username.toStdString() << "\n"
                             << currentLevel << "\n"
                             << currentQuest << "\n"
                             << currentProgress << "\n";
            }

            //Creates string from stringstream, needed to get const char*
            std::string returnString(packetStream.str());
            //Creates const char* to add into returning packet
            returnChars = returnString.c_str();

            packet << returnChars;
            client.send(packet);
        }
    }
}

void MainWindow::queryDatabaseUserCreate(QString name, QString password)
{
    sf::Packet packet;
    QSqlQuery query(db);

    QString theQuery = "Select * from Users where username = \"" + name + "\"";

     //Executes the query recieved from the client for user data
    query.exec(theQuery);

    if(query.size() != 0)
    {
        //send back failure number
            packet << "0";

            client.send(packet);
    }
    else
    {
        theQuery = "INSERT INTO Users (`username`, `password`) VALUES ('" + name + "', '" + password + "')";


        if( query.exec(theQuery))
        {
            packet << "1";
        }
        else
        {
            qDebug() << query.lastError();
            packet << "0";
        }

        client.send(packet);
    }
}

void MainWindow::queryDatabaseUserDelete(QString name)
{
    sf::Packet packet;
    QSqlQuery query(db);

    QString theQuery = "DELETE FROM Users WHERE `idUsers`= '" + name +"'";

     //Executes the query recieved from the client for user data
    query.exec(theQuery);

}

void MainWindow::createWebPage()
{
    std::ofstream outFile;
    outFile.open("..\..\webpage.html");

    QString theQuery = "Select * from Users";
    QSqlQuery query(db);

    std::stringstream htmlpage;
    htmlpage << "<html><head><title>PlantQuest Heuristics</title></head>"
    "<body><table align='left' border='1' cellpadding=\"10\"><caption align='top'><h2> Student List</h2>"
    "<tr><th> Student ID </th><th> Username </th><th> Password </th><th> Current Level</th><th> Current Quest </th><th> Current Progress </th></tr>";

    query.exec(theQuery);

    while (query.next())
    {
        int userID = query.value(0).toInt();
        QString username = query.value(1).toString();
        QString pass = query.value(2).toString();
        int currentLevel = query.value(3).toInt();
        int currentQuest = query.value(4).toInt();
        int currentProgress = query.value(6).toInt();

        htmlpage << "<tr>";

        htmlpage << "<td>"<< userID << "</td>"
                 << "<td>"<< username.toStdString() << "</td>"
                 << "<td>"<< pass.toStdString() << "</td>"
                 << "<td>"<< currentLevel << "</td>"
                 << "<td>"<< currentQuest << "</td>"
                 << "<td>"<< currentProgress << "</td>";

        htmlpage << "</tr>";
    }

    htmlpage << "</table ><div style=\"clear:both;\"></div>";

    htmlpage << "<table align='left' border='1' cellpadding=\"10\">"
                "<caption align='top'><h2> Category Leaders</h2>"
                "<tr><th></th><th> Username </th><th> Score</th>"
                "</tr><tr><td>Highest Level</td><td></td><td></td>"
                "</tr><tr><td>Highest Quest Number</td><td></td>"
                "<td></td></tr><tr><td>Longest Playtime</td><td>"
                "</td><td></td></tr><tr><td>Highest Quest/ Shortest Time</td>"
                "<td></td><td></td></tr></table><br/><br/><br/></body></html>";

    outFile << htmlpage.rdbuf();

    QDesktopServices::openUrl(QUrl("..\..\webpage.html"));

    outFile.close();
}

void MainWindow::on_pushButton_clicked()
{
    if (!connected)
    {
        setupConnection();
        ui->pushButton->setText("Close Connection");
    }
    else
    {
        closeConnection();
        ui->pushButton->setText("Open Connection");
    }

    connected = !connected;
}
