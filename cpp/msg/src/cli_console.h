#ifndef _CLI_CONSOLE_H_
#define _CLI_CONSOLE_H_

#if (defined __cplusplus) && (__cplusplus >= 201700L)
#include <optional>
#else
#include "optional.hpp"
#endif
#include <iostream>
#include <string>
#include <functional>
#include <curses.h>

#include "request.h"

enum State
{
    POLLING_COMMAND_STATE,

    COMPOSING_STRING_STATE,

    INVALID_STATE
};

class ConsoleInputHandler
{
public:
    struct CommandRet
    {
	std::optional<UserRequest> commType;
	std::optional<std::string> msg;
    };
    
    ConsoleInputHandler(void);
    // will be called when new message is received
    void Refresh(const std::string& msg);
    // when asked to send message
    std::string ComposeMessage(void) const;
    std::optional<CommandRet> InputKey(void);
    void DeleteCharacter(void);
    void MoveCursor(int x, int y);
    std::string GetCommand(void);
    std::string GetComposedMessage(void);
    std::string ReadContentsOfWindow(void);

    CommandRet CheckCommand(const std::string& c, const std::optional<std::string>& message);
private:
    std::string ClearSpacesFromWindowString(char* buf, uint32_t bufferSize);
    void GetContentsInWindow(char* buffer, uint32_t bufferSize);
private:
    static const char* COMMANDS[4];
    
    std::string m_commandPrompt;
    std::string m_message;
    WINDOW* m_commandWindow;
    State m_state;
};

#endif /* _CLI_CONSOLE_H_ */
