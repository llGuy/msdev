#include "cli_console.h"

const char* ConsoleInputHandler::COMMANDS[4]
{
    "disc",
    "usnme",
    "list",
    "send"
};

ConsoleInputHandler::ConsoleInputHandler(void)
{
    keypad(stdscr, true);
    PromptCommand();
}

void ConsoleInputHandler::Refresh(const std::string& msg) 
{
    std::cout << '\r' << msg << "\t\t\n";
    PromptCommand();
}

std::string ConsoleInputHandler::ComposeMessage(void) const
{
    // handle message using curses
}

void ConsoleInputHandler::PromptCommand(void) 
{
    m_command = "";
    std::cout <<  "\rcommand : " << std::flush;
}

ConsoleInputHandler::CommandRet ConsoleInputHandler::CheckCommand(void)
{
    if(m_command == COMMANDS[UserRequest::DISCONNECT]) return CommandRet{ UserRequest::DISCONNECT };
    else if(m_command == COMMANDS[UserRequest::USERNAME]) return CommandRet{ UserRequest::USERNAME, ComposeMessage() };
    else if(m_command == COMMANDS[UserRequest::LIST_AVAILABILITY]) return CommandRet{ UserRequest::LIST_AVAILABILITY };
    else if(m_command == COMMANDS[UserRequest::SEND]) return CommandRet{ UserRequest::SEND, ComposeMessage() };

    return CommandRet{};
}

void ConsoleInputHandler::InputKey(void) 
{
    char ch = getch();
    if(ch == '!')
    {
	PromptCommand();
    }
    else if(ch != -1)
    {
	std::cout << "user entered something" << std::endl;
    }
}
