#ifndef _SOCKET_H_
#define _SOCKET_H_

/* c functions for socket API */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <cstring>

#include <iostream>

using Byte = char;

class Socket
{
public:
    enum Interface
    {
	SERVER,

	CLIENT
    };

    Socket(int32_t recvflag = 0);
    Socket(const Socket&) = default;
    Socket(int32_t handle, const sockaddr_in& address, int32_t recvflag = 0);
    Socket(int32_t iptype, int32_t socktype, int32_t prototype, int32_t recvflag = 0);

    // close socket
    ~Socket(void) = default;
    
    void Connect(void);
    void Send(const Byte*, std::size_t size) const;
    bool Receive(Byte* buffer, std::size_t size) const;
    void Bind(void);
    void Listen(int32_t maxPending);
    void Close(void);
    Socket AcceptConnection(void) const;
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
    sockaddr_in& Address(void)
    {
	return m_serverAddress;
    }
    inline
    bool Connected(void)
    {
	return m_handle != 0;
    }
private:
    // init
    void EmptyServAddressStruct(void);
private:
    struct sockaddr_in m_serverAddress;
    int32_t m_handle;
    int32_t m_recvFlag;
};

#endif /* _SOCKET_H_ */
