#pragma once

/* c functions for socket API */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <cstring>

#include <iostream>

using Byte = int8_t;

class Socket
{
public:
    enum Interface
    {
	SERVER,

	CLIENT
    };

    Socket(void) = default;
    Socket(int32_t handle, const sockaddr_in& address);
    Socket(int32_t iptype, int32_t socktype, int32_t prototype);

    // close socket
    ~Socket(void) = default;

    void Connect(void);
    void Send(Byte*, std::size_t size) const;
    void Receive(Byte* buffer, std::size_t size) const;
    void Bind(void);
    void Listen(int32_t maxPending);
public:
    // init
    void IP(int32_t iptype, const std::string& pip);
    void IPFamily(int32_t family);
    void Port(const std::string& pport);

    void InaddrAny(void);
public:
    // getters
    inline
    int32_t Handle(void) const
    {
	return m_handle;
    }
    inline
    sockaddr_in& Adddress(void)
    {
	return m_serverAddress;
    }
private:
    // init
    void EmptyServAddressStruct(void);
private:
    struct sockaddr_in m_serverAddress;
    int32_t m_handle;
};
