#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include "practical.h"

#define BUFSIZE 512

int main(int argc, char* argv[])
{
    if(argc < 3 || argc > 4) // test for correct number of arguments
	DieWithUserMessage("parameters", "<Server Address> <Echo Word> [<Server Port>]");

    char* servIP = argv[1];   // first arg: server IP address (dotted quad)
    char* echoString = argv[2]; // second arg : string to echo

    // third arg (optional): server port (numeric)
    in_port_t servPort = (argc == 4) ? atoi(argv[3]) : 7;

    // create a reliable, stream socket using TCP
    // AF_INET = IPv4 using the stream based protocol SOCK_STREAM
    // called TCP (IPPROTO_TCP)
    // if socket() fails, it returns -1
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock < 0)
	DieWithSystemMessage("socket() failed");

    /*
      prepare address and establish connection
      to connect a socket, we have to specify the address and port to connect to.
      the sockaddr_in structure is defined to be a "container" for this information
      the call to memset ensures that any parts of the structure that we do not explicitly set
      is equal to 0
     */
    
    // construct the server address structure
    struct sockaddr_in servAddr;           // server address
    memset(&servAddr, 0, sizeof(servAddr));// zero out structure

    /*
      filling in the sockaddr_in
      the address family (AF_INET), Internet address, and port number
      the function inet_pton() converts the string representation of the server's internet address
      into 32-bit binary representation
      the server's port number was converted from a cmd line string to binary earlier
     */
    servAddr.sin_family = AF_INET;         // IPv4 address family
    // convert address
    
    int rtnVal = inet_pton(AF_INET, servIP, &servAddr.sin_addr.s_addr);
    if(rtnVal == 0)
	DieWithUserMessage("inet_pton() failed", "invalid address string");
    else if(rtnVal < 0)
	DieWithSystemMessage("inet_pton() failed");

    /*
      htons() ensures that the binary value is formatted as required by the API
     */
    servAddr.sin_port = htons(servPort); // server port
    
    // establish the connection to the echo server
    /*
      connect() function establishes a connection between the given socket and the one the identified by the 
      address
      sockaddr_in structure will store the connection
      the pointer to the sockaddr_in address 
      
     */
    if(connect(sock, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0)
	DieWithSystemMessage("connect() failed");
    
    size_t echoStringLen = strlen(echoString); // determine input length

    // send the string to the server
    // we find the length of the string. ptr to the echo string is passed to the send()
    // if send() returns -1, sending has failed
    size_t numBytes = send(sock, echoString, echoStringLen, 0);
    
    if(numBytes < 0)
	DieWithSystemMessage("send() failed");
    else if(numBytes != echoStringLen)
	DieWithUserMessage("send()", "send unexpected number of bytes");

    
    // recieve the same string back from the server
    unsigned int totalBytesRcvd = 0;  // count the total bytes received
    fputs("received: ", stdout);      // setup to print the echoed string
    while(totalBytesRcvd < echoStringLen)
    {
	char buffer[BUFSIZE];  // IO buffer
	/* receive up to the buffer size (minus 1 to leave space for a null terminator) bytes from the sender */
	numBytes = recv(sock, buffer, BUFSIZE - 1, 0);
	if(numBytes < 0)
	    DieWithSystemMessage("recv() failed");
	else if(numBytes == 0)
	    DieWithUserMessage("recv()", "connection closed prematurely");
	totalBytesRcvd += numBytes;  // keep tally of total bytes
	buffer[numBytes] = '\0';     // terminate string!
	fputs(buffer, stdout);
    }

    printf("\n");

    close(sock);
  
    return 0;
}
