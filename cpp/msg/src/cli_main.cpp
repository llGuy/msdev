#include "cli_client.h"
#include "cli_console.h"
#include <string>

int main(int argc, char* argv[])
{
    std::cout << "welcome to the Ultimate GUI chat application\n\n" << std::endl;
    TCPIPClient client;
    client.Init("192.168.1.230", "5000");
    /*  
    while(true)
    {
	// check for user commands
	cihandler.InputKey();
	auto command = cihandler.CheckCommand();
	client.ReceiveCommand(command);

	// check if user received message
	auto msg = client.ReceiveMessage();
	if(msg.has_value()) cihandler.Refresh(msg.value());
    }
*/
    
    client.List(ConsoleInputHandler::CommandRet{});
    
    auto msg = client.ReceiveMessage();
    if(msg.has_value())
    {
	std::cout << msg.value();
    }

    return 0;
}
