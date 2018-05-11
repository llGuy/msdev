#include <optional>
#include "cli_client.h"
#include "log.h"

TCPIPClient::TCPIPClient(void)
    : m_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)
{
}

void TCPIPClient::Init(const std::string& pip, const std::string& port)
{
    m_socket.IPFamily(AF_INET);
    m_socket.IP(AF_INET, pip);
    m_socket.Port(port);

    // connecting
    m_socket.Connect();
}

void TCPIPClient::SendMessage(const std::string& message)
{
    const Byte* msg = message.c_str();
    std::size_t msglength = message.length();
    m_socket.Send(msg, msglength);
}

std::optional<std::string> TCPIPClient::ReceiveMessage(void) const
{
    static constexpr uint32_t BUFFER_SIZE = 128;
    Byte destination[BUFFER_SIZE];
    bool res = m_socket.Receive(destination, BUFFER_SIZE);

    if(res) return { std::string(destination + 1) };
    return std::optional<std::string>{};
}

void TCPIPClient::ReceiveCommand(const ConsoleInputHandler::CommandRet& comm)
{
    auto& type = comm.commType;
    if(type.has_value())
    {
	switch(*type)
	{
	case UserRequest::DISCONNECT:       Disconnect(comm); return;
	case UserRequest::USERNAME:         Username(comm); return;
	case UserRequest::LIST_AVAILABILITY:List(comm); return;
	case UserRequest::SEND:             Send(comm); return;
	}
    }
    // hasn't received a command or hasn't received valid command
}

void TCPIPClient::Send(const ConsoleInputHandler::CommandRet& comm)
{
    auto& msg = comm.msg;
    if(msg.has_value())
    {
	std::string destinationUser;

	std::string finalMessage = destinationUser + static_cast<char>(RequestDelimiter::REQ_END_OF_USERNAME) + *msg;
	finalMessage.insert(0, 1, static_cast<char>(UserRequest::SEND));
	SendMessage(finalMessage);
    }
}
void TCPIPClient::List(const ConsoleInputHandler::CommandRet& comm)
{
    std::string msg = "list";
    msg.insert(0, 1, static_cast<char>(UserRequest::LIST_AVAILABILITY));
    SendMessage(msg);
}
void TCPIPClient::Username(const ConsoleInputHandler::CommandRet& comm)
{
    auto& msg = comm.msg;
    if(msg.has_value())
    {
	std::string msge(msg.value());
	msge.insert(0, 1, static_cast<char>(UserRequest::USERNAME));
	SendMessage(msge);
    }
}
void TCPIPClient::Disconnect(const ConsoleInputHandler::CommandRet& comm)
{
    std::string msg = "disc";
    msg.insert(0, 1, static_cast<char>(UserRequest::DISCONNECT));
    SendMessage(msg);
}

bool TCPIPClient::Connected(void)
{
    return m_socket.Handle() != 0;
}
