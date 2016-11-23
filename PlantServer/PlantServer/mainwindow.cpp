#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
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
        std::cout << "Msg received: " << msg << std::endl;
        recievedQuery = QString::fromStdString(msg);


        queryDatabase();
    }


    // Use a timer to keep checking for packets while keeping the GUI alive
    QTimer::singleShot(100, this, SLOT(getPackets()));

}

void MainWindow::connectToDatabase()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("plantquestdb.ck8fat1uoilr.us-west-2.rds.amazonaws.com");
    db.setPort(3306);
    db.setDatabaseName("PlantQuestDB");
    db.setUserName("plantadmin");
    db.setPassword("plantpassword");
    qDebug() << db.open();

}

void MainWindow::queryDatabase()
{
    qDebug() << db.open();
    QSqlQuery query(db);

    query.exec(recievedQuery);

    while (query.next())
    {
        int plantIndex = query.value(0).toInt();
        QString name = query.value(1).toString();
        qDebug() << plantIndex << name;
    }

}

void MainWindow::on_pushButton_clicked()
{
    if (!connected) {
        setupConnection();
        ui->pushButton->setText("Close Connection");
    }
    else {
        closeConnection();
        ui->pushButton->setText("Open Connection");
    }
    connected = !connected;
}
