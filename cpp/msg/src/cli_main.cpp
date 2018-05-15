#include "cli_client.h"
#include "cli_message.h"
#include "cli_console.h"
#include <string>

int main(int argc, char* argv[])
{
    std::cout << "welcome to the Ultimate GUI chat application\n\n" << std::endl;
    TCPIPClient client;
    client.Init("81.187.137.2 31", "5000");
    
    ConsoleInputHandler cihandler;
    for(;;)
    {
	auto comm = cihandler.InputKey();
	if(comm.has_value())
	    client.ReceiveCommand(comm.value());

	auto m = client.ReceiveMessage();
	if(m.has_value())
	{
	    Message message = m.value();
	    message.Parse();
	    cihandler.Refresh(message.Str());
	}
    }

    return 0;
}
