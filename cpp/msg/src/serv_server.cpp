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

void Server::Accept(Byte* destination, std::size_t destBuffersize)
{
    Socket clientSocket(m_socket.AcceptConnection());
    sockaddr_in& clientAddress = clientSocket.Address();
    
    char clientName[INET_ADDRSTRLEN];
    const char* err = inet_ntop(AF_INET, &clientAddress.sin_addr.s_addr, clientName, sizeof(clientName));
    // handle errors
    if(err == NULL)
	std::cout << "unable to handle client address" << '\n';

    // initialize new socket
    Connection& us = **m_connectionDataBase.AtIP(std::string{clientName}, m_socket);
    us.Sock() = clientSocket;
}

void Server::InitAddressStruct(const std::string& port)
{
    m_socket.InaddrAny();
    m_socket.IPFamily(AF_INET);
    m_socket.Port(port);
}

void Server::SendMessage(Connection& conn, const Byte* data, ServerRequest request)
{
    int8_t first = static_cast<int8_t>(request);
    std::string msg(data);
    msg.insert(0, 1, first);
    conn.Send(msg);
}
