#include "algorithm.h"
#include "cli_message.h"

Message::Message(const std::string& m)
    : m_message(m)
{
}

void Message::Parse(void)
{
    char first = m_message[0];
    switch(first)
    {
    case static_cast<char>(ServerRequest::LIST_AVAILABILITY):
	ParseListRequest(); break;
    case static_cast<char>(ServerRequest::SEND):
	ParseSendRequest(); break;
    }
}

void Message::ParseListRequest(void)
{
    // erase first character (code) so that message is printable
    m_message.erase(m_message.begin());
}

void Message::ParseSendRequest(void)
{
    m_message.erase(m_message.begin());
    
    std::string fromUser = CopyBefore(m_message, static_cast<char>(RequestDelimiter::REQ_END_OF_USERNAME)); 
    std::string actualMessage = m_message.substr(fromUser.size() + 2);

    m_message = fromUser + " > " + actualMessage;
}

std::ostream& operator<<(std::ostream& os, const Message& m)
{
    os << m.Str();
    return os;
}
