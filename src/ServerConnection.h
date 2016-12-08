#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <SFML/Network.hpp>
#include <QString>

class ServerConnection
{
public:
    ServerConnection();
    void setupConnection();
    void sendPacket(std::string query);
    QString getPacket();

private:
    std::string host;
    int port;
    sf::TcpSocket socket;

};

#endif // SERVERCONNECTION_H
