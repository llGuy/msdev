#include "serv_connection.h"

Connection::Connection(void)
    : m_boundIP(), m_boundID(-1)
{
}

Connection::Connection(const std::string& pip, std::size_t id)
    : m_boundIP(pip), m_boundID(id)
{
}

Connection::Connection(const std::string& name, const std::string& ip, Socket sock)
    : m_boundUsername(name), m_boundIP(ip), m_socket(sock)
{
}

void Connection::Send(const std::string& msg)
{
    std::cout << "sending message to " << m_boundUsername << " : message = " << msg << '\n';
    m_socket.Send(msg.c_str(), msg.size());
}

void Connection::Receive(Byte* buffer, std::size_t size) const
{
    m_socket.Receive(buffer, size);
}
