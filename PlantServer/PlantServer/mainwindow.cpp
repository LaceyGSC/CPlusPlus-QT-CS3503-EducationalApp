#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <sstream>
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

        //Starts query to database for plant data
        //Will use switch statement for different query types later
        queryDatabasePlant();
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

    //Executes the query recieved from the client for plant data
    query.exec(recievedQuery);

    while (query.next())
    {
        //Gets plant index info
        QString name = query.value(1).toString();
        QString latinName = query.value(2).toString();
        QString description = query.value(3).toString();
        QString uses = query.value(4).toString();
        QString location = query.value(5).toString();

        //Adds all plant info to stringstream
        packetStream << name.toStdString() <<": " << latinName.toStdString() << "\n"
                     << description.toStdString() << "\n"
                     << uses.toStdString() << "\n"
                     << location.toStdString() << "\n \n";

//        packetStream.clear();
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

void MainWindow::queryDatabaseUser()
{
    sf::Packet packet;
    std::stringstream packetStream;
    const char* returnChars;
    QSqlQuery query(db);

    //Executes the query recieved from the client for user data
    query.exec(recievedQuery);

    while (query.next())
    {
        //build query for user information to match against
    }

//    std::string returnString(packetStream.str());
//    returnChars = returnString.c_str();

//    packet << returnChars;

//    client.send(packet);

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
