#include "cli_console.h"
#include "algorithm.h"

const char* ConsoleInputHandler::COMMANDS[4]
{
    "disc",
    "usrn",
    "list",
    "send"
};

ConsoleInputHandler::ConsoleInputHandler(void)
    : m_state(State::POLLING_COMMAND_STATE)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    // window at the bottom of screen
    m_commandWindow = newwin(5, COLS, LINES - 5, 0);
    refresh();
    box(m_commandWindow, (int)' ', 0);
    wmove(m_commandWindow, 1, 1);
    wrefresh(m_commandWindow);
}

void ConsoleInputHandler::Refresh(const std::string& msg) 
{
    waddstr(stdscr, msg.c_str());
    refresh();
}

std::string ConsoleInputHandler::ComposeMessage(void) const
{
    // handle message using curses
}

ConsoleInputHandler::CommandRet ConsoleInputHandler::CheckCommand(const std::string& command, const std::optional<std::string>& message)
{
    std::string commandKeyword = CopyBefore(command, ' ');
    
    if(commandKeyword == COMMANDS[UserRequest::DISCONNECT]) return CommandRet{ UserRequest::DISCONNECT };
    else if(commandKeyword == COMMANDS[UserRequest::USERNAME])
    {
	return CommandRet{ UserRequest::USERNAME, std::string(command.substr(commandKeyword.size() + 1)) };
    }
    else if(commandKeyword == COMMANDS[UserRequest::LIST_AVAILABILITY]) return CommandRet{ UserRequest::LIST_AVAILABILITY };
    else if(commandKeyword == COMMANDS[UserRequest::SEND])
    {
	if(message.has_value())
	    return CommandRet{ UserRequest::SEND, message.value() };
	m_state = State::COMPOSING_STRING_STATE;
    }

    return CommandRet{};
}

void ConsoleInputHandler::DeleteCharacter(void)
{
    int rows, cols;
    nocbreak();
    getyx(m_commandWindow, rows, cols);
    wmove(m_commandWindow, rows, cols - 1);
    wdelch(m_commandWindow);
    cbreak();
    wrefresh(m_commandWindow);
}

void ConsoleInputHandler::MoveCursor(int x, int y)
{
    int rows, cols;
    nocbreak();
    getyx(m_commandWindow, rows, cols);
    wmove(m_commandWindow, rows + y, cols + x);
    cbreak();
    wrefresh(m_commandWindow);
}

std::string ConsoleInputHandler::ClearSpacesFromWindowString(char* str, uint32_t bufferSize)
{
    uint32_t i = bufferSize - 1;
    while(str[--i] == ' ');
    str[i + 1] = '\0';
    return std::string(str);
}

std::string ConsoleInputHandler::GetCommand(void)
{
    static constexpr uint32_t BUFFER_SIZE = 64;
    char buffer[BUFFER_SIZE] { 0 };
    
    GetContentsInWindow(buffer, BUFFER_SIZE);

    return ClearSpacesFromWindowString(buffer, BUFFER_SIZE);
}

void ConsoleInputHandler::GetContentsInWindow(char* buffer, uint32_t bufferSize)
{
    wmove(m_commandWindow, 1, 1);
    winnstr(m_commandWindow, buffer, bufferSize);
    wclear(m_commandWindow);
    box(m_commandWindow, (int)' ', 0);
    wmove(m_commandWindow, 1, 1);
    wrefresh(m_commandWindow);
}

std::string ConsoleInputHandler::GetComposedMessage(void)
{
    static constexpr uint32_t BUFFER_SIZE = 64;
    char buffer[BUFFER_SIZE] { 0 };

    GetContentsInWindow(buffer, BUFFER_SIZE);

    return ClearSpacesFromWindowString(buffer, BUFFER_SIZE);
}

std::optional<ConsoleInputHandler::CommandRet> ConsoleInputHandler::InputKey(void) 
{
    char ch = getch();
    if(ch != ERR)
    {
	if(ch == 7 /*backspace*/) DeleteCharacter();
	else if(ch == KEY_LEFT) MoveCursor(-1 ,0);
	else if(ch == KEY_RIGHT) MoveCursor(1, 0);
	else if(ch == KEY_UP) MoveCursor(0, 1);
	else if(ch == KEY_DOWN) MoveCursor(0, -1);
	else if(ch == 10)
	{
	    if(m_state == State::POLLING_COMMAND_STATE)
	    {
		std::string command = GetCommand(); // end command
		wrefresh(m_commandWindow);
		return CheckCommand(command, std::optional<std::string>{});
	    }
	    else
	    {
		std::string command = "send";
		std::string message = GetComposedMessage();
		// reset state to command polling
		m_state = State::POLLING_COMMAND_STATE;
		return CheckCommand(command, std::optional<std::string>(message));
	    }
	}

	else waddch(m_commandWindow, ch);
    }
    wrefresh(m_commandWindow);

    return std::optional<CommandRet>{};
}
