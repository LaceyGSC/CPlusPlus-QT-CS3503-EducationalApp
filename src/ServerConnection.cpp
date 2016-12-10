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
    host = "localhost";
    port = 53001;

}

void ServerConnection::setupConnection()
{
    sf::Socket::Status status = socket.connect(host, port);
    socket.setBlocking(false);
}

void ServerConnection::sendPacket(std::string query)
{
    sf::Packet outPacket;

    //Adds a const char* to packet to be sent. must convert to const char* to use
    outPacket << query;
    socket.send(outPacket);

    //Calls method to get returning data.
    //BUG: Needs to be set to non-blocking
    //getPacket();
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
        recievedData = QString::fromStdString(data);

    }

    //Returns a QString with all of the data from the packet
    return recievedData;
}
