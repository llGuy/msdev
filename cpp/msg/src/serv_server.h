#ifndef _SERV_SERVER_H_
#define _SERV_SERVER_H_

#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "socket.h"
#include "request.h"
#include "serv_connection.h"
#include "serv_connection_data_base.h"

class Server
{
public:
    Server(void);
    Server(const Server&) = delete;
    const Server& operator=(const Server&) = delete;

    void Launch(const std::string& port);
    void Accept(Byte* destination, std::size_t destBuffersize);
private:
    // init
    void InitAddressStruct(const std::string& port);

//    void HandleRequest(Byte* data, std::size_t destBuffersize, Connection& user);
    void SendMessage(Connection& user, const Byte* data, ServerRequest request);
private:
    static constexpr int32_t MAX_PENDING = 5;
    
    Socket m_socket;
    ConnectionDataBase m_connectionDataBase;
};


#endif /* _SERV_SERVER_H_ */
