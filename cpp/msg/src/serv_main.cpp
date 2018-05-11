#include "serv_server.h"

int main(int argc, char* argv[])
{
    Server server;
    server.Launch("5000");

    for(;;)
    {
	static constexpr std::size_t BUFFER_SIZE = 64;
	Byte buffer[BUFFER_SIZE];
	server.Accept(buffer, BUFFER_SIZE);
    }
    
    return 0;
}
