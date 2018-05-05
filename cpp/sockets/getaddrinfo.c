#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include "practical.h"

int main(int argc, char* argv[])
{
    if(argc != 3) // test for correct number of arguments
	DieWithUserMessage("Parameters", "<Address/Name> <Port Service>");
  
    char* addrString = argv[1]; // server address/ name
    char* portString = argv[2]; // server port/service

    // tell the system what kinds of address info we want
    struct addrinfo addrCriteria; // criteria for address match
    memset(&addrCriteria, 0, sizeof(addrCriteria)); // zero out structure
    addrCriteria.ai_family = AF_UNSPEC; // any address family
    addrCriteria.ai_socktype = SOCK_STREAM; // only stream sockets
    addrCriteria.ai_protocol = IPPROTO_TCP; // only TCP protocol


    // we need to pass the desired hostname to the addrinfo
    // get address associated with the specified name/service
    struct addrinfo* addrList; // holder for list of addresses returned
    // modify servAddr contents to reference linked list of addresses
    int rtnVal = getaddrinfo(addrString, portString, &addrCriteria, &addrList);
    // returns 0 if successful. gai_strerror gets the error message associated
    // to the return values
    if(rtnVal != 0)
	DieWithUserMessage("getaddrinfo() failed", gai_strerror(rtnVal));
    
    // display returned addresses
    for(struct addrinfo* addr = addrList; addr != NULL; addr = addr->ai_next)
    {
	PrintSocketAddress(addr->ai_addr, stdout);
	printf("\n");
    }
    
    freeaddrinfo(addrList); // free addrinfo allocated in getaddrinfo()
    exit(0);
}
