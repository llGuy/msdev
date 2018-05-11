#ifndef _CLI_CONSOLE_H_
#define _CLI_CONSOLE_H_

#include <iostream>
#include <string>
#include <functional>
#include <curses.h>

#include "request.h"

class ConsoleInputHandler
{
public:
    ConsoleInputHandler(void);
    // will be called when new message is received
    void Refresh(const std::string& msg);
    // when asked to send message
    std::string ComposeMessage(void) const;
    void PromptCommand(void);

    void InputKey(void);

    struct CommandRet
    {
	std::optional<UserRequest> commType;
	std::optional<std::string> msg;
    };
    CommandRet CheckCommand(void);
private:
    static const char* COMMANDS[4];
    
    std::string m_commandPrompt;
    std::string m_command;
};

#endif /* _CLI_CONSOLE_H_ */
