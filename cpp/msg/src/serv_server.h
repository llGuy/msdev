#pragma once

#include "socket.h"

class Server
{
public:
    //Server(void) = default;
    Server(void);

    void Launch(const std::string& port);
    void Accept(void);
private:
    // init
    void InitAddressStruct(const std::string& port);
private:
    static constexpr int32_t MAX_PENDING = 5;
    
    Socket m_socket;
};
