#ifndef _SERV_CONNECTION_H_
#define _SERV_CONNECTION_H_

#include <string>
#include <thread>
#include <memory>

#include "socket.h"

class Connection
{
public:
    Connection(void);
    Connection(const std::string& pip, std::size_t id);
    Connection(const std::string& name, const std::string& ip, Socket sock);

    void Send(const std::string& msg);
    bool Receive(Byte* buffer, std::size_t size) const;
    
    inline
    Socket& Sock(void)
    {
	return m_socket;
    }
    inline
    void Disable(void)
    {
	m_boundID = -1;
	m_boundUsername = "null";
	m_boundIP = "0.0.0.0";
    }
    inline
    const std::string& BoundIP(void) const
    {
	return m_boundIP;
    }
    inline
    std::string& BoundUsername(void) 
    {
	return m_boundUsername;
    }
    inline
    std::size_t BoundID(void) const
    {
	return m_boundID;
    }

private:
    std::string m_boundUsername;
    std::string m_boundIP;
    std::size_t m_boundID;
    Socket m_socket;
};

#endif /* _SERV_CONNECTION_H_ */
