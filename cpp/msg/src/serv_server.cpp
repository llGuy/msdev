#include "serv_server.h"

Server::Server(void)
    : m_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)
{
}

void Server::Launch(const std::string& port)
{
    InitAddressStruct(port);
    m_socket.Bind();
    m_socket.Listen(MAX_PENDING);
}

void Server::Accept(void)
{
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    int32_t clientSocketHandle = accept(m_socket.Handle(), (struct sockaddr*)(&clientAddress), &clientAddressLength);
    // create socket
    Socket clientSocket(clientSocketHandle, clientAddress);
}

void Server::InitAddressStruct(const std::string& port)
{
    m_socket.InaddrAny();
    m_socket.IPFamily(AF_INET);
    m_socket.Port(port);
}

