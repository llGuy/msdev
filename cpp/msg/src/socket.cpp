#include <string>

#include "socket.h"

#define DEBUG true

Socket::Socket(void)
    : m_handle(0)
{
}

Socket::Socket(int32_t handle, const sockaddr_in& address)
    : m_handle(handle), m_serverAddress(address)
{
}

Socket::Socket(int iptype, int socktype, int prototype)
    : m_handle(socket(iptype, socktype, prototype))
{
    if(m_handle < 0) std::cerr << "socket() failed\n";
    EmptyServAddressStruct();
}

void Socket::EmptyServAddressStruct(void)
{
    memset(&m_serverAddress, 0, sizeof(m_serverAddress));
}

void Socket::Connect(void)
{
    int val = connect(m_handle, (struct sockaddr*)(&m_serverAddress), sizeof(m_serverAddress));
    if(val < 0) std::cerr << "connect() failed";
}

void Socket::Send(const Byte* data, std::size_t size) const
{
    std::size_t numBytes = send(m_handle, data, size, 0);
    
    if(numBytes < 0) std::cerr << "send() failed\n";
    else if(numBytes != size) std::cerr << "send() " << "sent unexpected number of bytes " << numBytes << "\n";
}

bool Socket::Receive(Byte* buffer, std::size_t size) const
{
    int32_t bytesReceived = recv(m_handle, buffer, size - 1, 0);
    
    return bytesReceived > 0;
}

void Socket::Bind(void)
{
    bind(m_handle, (struct sockaddr*)(&m_serverAddress), sizeof(m_serverAddress));
}

void Socket::Listen(int32_t maxPending)
{
    listen(m_handle, maxPending);
}

void Socket::IPFamily(int32_t family)
{
    m_serverAddress.sin_family = family;
}

void Socket::IP(int32_t iptype, const std::string& pip)
{
    std::cout << pip << std::endl;
    
    int val = inet_pton(iptype, pip.c_str(), &m_serverAddress.sin_addr.s_addr);

    std::cout << val << std::endl;
    
    if(val == 0) std::cerr << "inet_pton() failed : " << "invalid address string\n";
    else if(val < 0) std::cerr << "inet_pton() failed\n";
}

void Socket::Port(const std::string& pport)
{
    int32_t port = atoi(pport.c_str());
    m_serverAddress.sin_port = htons(port);
}

void Socket::InaddrAny(void)
{
    m_serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
}

void Socket::Close(void)
{
    m_handle = 0;
    if(shutdown(m_handle, 2) == -1)
	std::cerr << "unable to shutdown socket\n";
}

Socket Socket::AcceptConnection(void) const
{
    sockaddr_in address;
    socklen_t addressLength = sizeof(address);
    int32_t newSocket = accept(m_handle, (sockaddr*)(&address), &addressLength);
    return Socket(newSocket, address);
}
