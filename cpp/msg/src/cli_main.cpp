#include "cli_client.h"
#include "cli_console.h"
#include <string>

int main(int argc, char* argv[])
{
    std::cout << "welcome to the Ultimate GUI chat application\n\n" << std::endl;
    TCPIPClient client;
    client.Init("192.168.1.230", "5000");

    client.Username(ConsoleInputHandler::CommandRet{ {}, "luc rosenzweig"});
    std::cin.get();
    client.List(ConsoleInputHandler::CommandRet{});
    std::cout << "sent message\n";
    
    auto msg = client.ReceiveMessage();
    if(msg.has_value())
    {
	std::cout << msg.value() << std::endl;
    }

    std::cout << "preparing to send message to luc rosenzweig" << std::endl;
    std::cin.get();
    // sending message to myself
    std::string message = "hello friend!";
    client.Send({ {}, message }, "luc rosenzweig");

    std::cin.get();
    auto msg2 = client.ReceiveMessage();
    if(msg2.has_value())
    {
	std::cout << msg2.value() << std::endl;
    }

    return 0;
}
