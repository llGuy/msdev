#ifndef _SERV_CONNECTION_DATA_BASE_H_
#define _SERV_CONNECTION_DATA_BASE_H_

#include <new>
#include <array>
#include <tuple>
#include <string>
#if (defined __cplusplus) && (__cplusplus >= 201700L)
#include <optional>
#else
#include "optional.hpp"
#endif
#include <iterator>
#include <algorithm>

#include "log.h"
#include "serv_connection.h"

class ConnectionDataBase
{
public:
    ConnectionDataBase(void)
	:   m_numConnections(0)
    {
    }

    void Disconnect(const std::string& pip)
    {
	for(std::size_t i = 0; i < MAX_CONNECTIONS; ++i)
	{
	    Connection& c = m_connections[i];
	    if(c.BoundIP() == pip)
	    {
		NewLog(c.BoundUsername() + " disconnected");
		c.Disable();
		m_threads[i].reset();
	    }
	}
    }
    
    std::optional<Connection*> AtIP(const std::string& pip, const Socket& servSocket)
    {
	for(std::size_t i = 0; i < MAX_CONNECTIONS; ++i)
	{
	    Connection& connection = m_connections[i];
	    if(connection.BoundIP() == pip) return &m_connections[i];
	    if(connection.BoundID() == -1) return &AddConnection(pip, i, servSocket);
	}
	// there are too many users
	return std::optional<Connection*>{};
    }
    
    std::optional<Connection*> AtName(const std::string& username)
    {
	std::optional<Connection*> ret;
	std::for_each(m_connections.begin(), m_connections.end(), [&](Connection& c)
		      {
			  if(c.BoundUsername() == username) ret = &c;
		      });
	return ret;
    }

    std::string ListConnectedUsers(void)
    {
	std::string connections;
	std::for_each(m_connections.begin(), m_connections.end(), [&connections](Connection& c)
		 {
		     if(c.BoundID() != -1) connections += c.BoundUsername() + '\n';
		 });
	return connections;
    }

    Connection& operator[](std::size_t i)
    {
	return m_connections[i];
    }
private:
    Connection& AddConnection(const std::string& pip, std::size_t ptr, const Socket& servSocket)
    {
	new(&(m_connections[ptr])) Connection(pip, ptr);
	// default name
	m_connections[ptr].BoundUsername() = "client" + std::to_string(ptr);

	NewLog(m_connections[ptr].BoundUsername() + " user joined server ");
	
	m_threads[ptr] = std::make_unique<std::thread>(&ConnectionDataBase::Communicate, this, servSocket, ptr);
	
	return m_connections[m_numConnections++];
    }

    std::string AvailableUsers(void)
    {
	std::string connections = "available users : \n";
	std::for_each(m_connections.begin(), m_connections.end(), [&](Connection& c)
		      {
			  if(c.BoundID() != -1) connections += std::string(" - ") + c.BoundUsername() + '\n';
		      });
	return connections;
    }

    std::string ExtractUsernameFromRequest(const std::string& msg) const
    {
	std::string username;
	for(uint32_t i = 1; msg[i] != static_cast<char>(RequestDelimiter::REQ_END_OF_USERNAME); ++i)
	{
	    username.push_back(msg[i]);
	}
	return username;
    }

    void SendMessage(ServerRequest r, const std::string& data, Connection& c)
    {
	int8_t first = static_cast<int8_t>(r); 
	std::string msg(data);
	Log("sending message to " + c.BoundUsername() + " : \n" + msg);
	msg.insert(0, 1, first); 
	c.Send(msg);
    }
    
    void HandleRequest(Byte* data, const Socket& servSocket, Connection& c)
    {
	UserRequest first = static_cast<UserRequest>(*data);
	std::string raw(data);
	switch(first)
	{
	case UserRequest::DISCONNECT: { Disconnect(c.BoundIP()); break; }
	case UserRequest::USERNAME: {
	    std::string old = c.BoundUsername();
	    c.BoundUsername() = raw.substr(1);
	    Log(old + " changed username to " + c.BoundUsername());
	    break; }
	case UserRequest::LIST_AVAILABILITY: {
	    Log("list availability request from " + c.BoundUsername());
	    std::string users(AvailableUsers());
	    // send the available users back to the requesting client
	    SendMessage(ServerRequest::LIST_AVAILABILITY, users, c);
	    break; }
	case UserRequest::SEND: {
	    std::optional<Connection*> conn = AtName(ExtractUsernameFromRequest(raw));

	    if(conn.has_value())
	    {
		Connection& clientConnection = **conn;
		Log(c.BoundUsername() + " requested to send message to " + clientConnection.BoundUsername()); 
		std::string requestingUsername = c.BoundUsername();
		std::string message(requestingUsername);
		message += static_cast<int8_t>(RequestDelimiter::REQ_END_OF_USERNAME);
	        message += raw.substr(clientConnection.BoundUsername().size() + 1 /* first character */);
		SendMessage(ServerRequest::SEND, message, clientConnection);
	    }
	    break;  }
	};
    }
    void Communicate(const Socket& servSocket, std::size_t i)
    {
	Connection& connection = m_connections[i];
	Log(std::string("launched new communication thread with ") + connection.BoundUsername());
	// while the connection is enabled
	while(connection.BoundID() != -1)
	{
	    static constexpr std::size_t BUFFER_SIZE = 64;
	    Byte buffer[BUFFER_SIZE] { 0 };
	    if(connection.Receive(buffer, BUFFER_SIZE))
	    {
		Log("received request from " + connection.BoundUsername());
		HandleRequest(buffer, servSocket, connection);
	    }
	}
    }
private:
    static constexpr int32_t MAX_CONNECTIONS = 5;
    
    std::array<Connection, MAX_CONNECTIONS> m_connections;
    std::array<std::unique_ptr<std::thread>, MAX_CONNECTIONS> m_threads;
    std::size_t m_numConnections;
};



#endif /* _SERV_CONNECTION_DATA_BASE_H_ */
