#include "ServerConnection.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <SFML/Network.hpp>
#include <iostream>


ServerConnection::ServerConnection()
{

    sf::Socket::Status status = socket.connect("localhost", 53001);

}

void ServerConnection::sendPacket(std::string query)
{
    sf::Packet outPacket;
    outPacket << "Select * from PlantTable";
    socket.send(outPacket);
}
