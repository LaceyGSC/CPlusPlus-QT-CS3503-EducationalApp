#include "ServerConnection.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <SFML/Network.hpp>
#include <iostream>
#include <QDebug>
#include <QTimer>


ServerConnection::ServerConnection()
{
    //Connects to the server on the localhost at this port
    sf::Socket::Status status = socket.connect("localhost", 53001);

}

void ServerConnection::sendPacket(std::string query)
{
    sf::Packet outPacket;

    //Adds a const char* to packet to be sent. must convert to const char* to use
    outPacket << "Select * from PlantTable";
    socket.send(outPacket);

    //Calls method to get returning data.
    //BUG: Needs to be set to non-blocking
    getPacket();
}

QString ServerConnection::getPacket()
{
    sf::Packet packet;
    QString recievedData;

    if (socket.receive(packet) == sf::Socket::Done)
    {
        //Socket is getting data back, changing to string
        std::string data;
        packet >> data;

        //Outputs and converts to QString, which QApplication likes better
        qDebug() << "Client return data: \n" << data <<"\n";
        recievedData = QString::fromStdString(data);
    }

    //Returns a QString with all of the data from the packet
    return recievedData;
}
