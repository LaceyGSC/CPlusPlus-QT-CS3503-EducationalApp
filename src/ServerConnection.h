#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <SFML/Network.hpp>
#include <QString>

class ServerConnection
{
public:
    ServerConnection();
    void sendPacket(std::string query);
    QString ServerConnection::getPacket();

private:
    sf::TcpSocket socket;

};

#endif // SERVERCONNECTION_H
