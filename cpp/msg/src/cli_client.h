#ifndef _CLI_CLIENT_H_
#define _CLI_CLIENT_H_

#include <optional>
#include <string>
#include "socket.h"
#include "cli_console.h"
 
class TCPIPClient
{
public:
    TCPIPClient(void);
    ~TCPIPClient(void) = default;

    bool Connected(void);
    void Init(const std::string& pip, const std::string& port);
    std::optional<std::string> ReceiveMessage(void) const;
    void ReceiveCommand(const ConsoleInputHandler::CommandRet& comm);
    void SendMessage(const std::string& message);
public:
    void Send(const ConsoleInputHandler::CommandRet& comm, /*debugging*/ const std::string& dest);
    void List(const ConsoleInputHandler::CommandRet& comm);
    void Username(const ConsoleInputHandler::CommandRet& comm);
    void Disconnect(const ConsoleInputHandler::CommandRet& comm);
private:
    Socket m_socket;
};


#endif /* _CLI_CLIENT_H_ */
