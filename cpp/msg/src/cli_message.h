#ifndef _CLI_MESSAGE_H_
#define _CLI_MESSAGE_H_

#include <string>
#include <iostream>
#include <algorithm>

#include "request.h"

class Message
{
public:
    Message(void) = default;
    Message(const std::string& m);
    void Parse(void);

    inline
    const std::string& Str(void) const
    {
	return m_message;
    }

    friend std::ostream& operator<<(std::ostream& os, const Message& m);
private:
    void ParseListRequest(void);
    void ParseSendRequest(void);
private:
    // originally contains raw message
    // after parsing process, string will contain
    // a printable version of the raw message
    std::string m_message;
};

#endif /* _CLI_MESSAGE_H_ */
