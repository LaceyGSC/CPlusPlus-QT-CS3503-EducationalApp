#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <SFML/Network.hpp>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <iostream>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setupConnection();
    void closeConnection();

private slots:
    void getPackets();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    // Open a listener on a port
    sf::TcpListener listener;
    // Talk over a TCP socket
    sf::TcpSocket client;
    bool connected;
    QString recievedQuery;

    QSqlDatabase db;

    void connectToDatabase();
    void queryDatabasePlant();
    void queryDatabaseUserLogin(QString name, QString password);
    void queryDatabaseUserCreate(QString name, QString password);
    void queryDatabaseUserDelete(QString name);
    void createWebPage();
};

#endif // MAINWINDOW_H
