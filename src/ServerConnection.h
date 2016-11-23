#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <SFML/Network.hpp>

class ServerConnection
{
public:
    ServerConnection();
    void sendPacket(std::string query);

private:
    sf::TcpSocket socket;

};

#endif // SERVERCONNECTION_H
