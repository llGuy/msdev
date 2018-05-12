#ifndef _REQUEST_H_
#define _REQUEST_H_

#include <stdint.h>

/*
  when requesting to send a message to another user
  user must put [character code for sending messages] + [destination user] +
  [username delimiter] + [message]
*/

enum UserRequest
: int8_t
{    
    DISCONNECT,

    USERNAME,

    LIST_AVAILABILITY,

    SEND,

    INVALID
};

enum class ServerRequest
: int8_t
{
    LIST_AVAILABILITY,

    SEND,

    INVALID
};

enum class RequestDelimiter
: int8_t
{
    REQ_END_OF_USERNAME = 1,

    INVALID = 2
};


#endif /* _REQUEST_H_ */
