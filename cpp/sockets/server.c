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

void HandleTCPClient(int clntSocket)
{
    char buffer[BUFSIZE]; // buffer for echo string

    // recieve message from client
    ssize_t numBytesRcvd = recv(clntSocket, buffer, BUFSIZE, 0);
    if(numBytesRcvd < 0)
	DieWithSystemMessage("recv() failed");

    // send received string and receive again until end of stream
    while(numBytesRcvd > 0) // 0 indicates end of stream
    {
	// echo message back to client
	ssize_t numBytesSent = send(clntSocket, buffer, numBytesRcvd, 0);
	if(numBytesSent < 0)
	    DieWithSystemMessage("send() failed");
	else if(numBytesSent != numBytesRcvd)
	    DieWithUserMessage("send()", "sent unexpected number of bytes");

	// see if there is more data to receive
	numBytesRcvd = recv(clntSocket, buffer, BUFSIZE, 0);
	if(numBytesRcvd < 0)
	    DieWithSystemMessage("recv() failed");

	printf(buffer);

	close(clntSocket); // close client socket
    }
}

static const int MAXPENDING = 5; // maximum outstanding connection requests

int main(int argc, char* argv[])
{
    if(argc != 2) // test for correct number of args
	DieWithUserMessage("parameters, ", "<Server Port>");

    in_port_t servPort = atoi(argv[1]);// first arg : local port
    // create socket for incoming connections
    int servSock; // socket descriptor for server
    if((servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	DieWithSystemMessage("socket() failed");

    // construct local address structure
    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));  // zero out structure
    servAddr.sin_family = AF_INET;           // IPv4 address familyx
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); // any incoming interface
    servAddr.sin_port = htons(servPort);          // local port

    // bind to the local address
    if(bind(servSock, (struct sockaddr*) &servAddr, sizeof(servAddr)) < 0)
	DieWithSystemMessage("bind() failed");

    // mark the socket so it will listen for incoming connections
    if(listen(servSock, MAXPENDING) < 0)
	DieWithSystemMessage("listen() failed");

    // run forever
    for(;;)
    {
	struct sockaddr_in clntAddr; // client address
	// set length of client address struct (in-out param)
	socklen_t clntAddrLen = sizeof(clntAddr);

	// wait for a client to connect
	int clntSock = accept(servSock, (struct sockaddr*) &clntAddr, &clntAddrLen);
	if(clntSock < 0)
	    DieWithSystemMessage("accept() failed");

	// clntSock is connected to client
	char clntName[INET_ADDRSTRLEN]; // string to contain client address
	if(inet_ntop(AF_INET, &clntAddr.sin_addr.s_addr, clntName, sizeof(clntName)) != NULL)
	    printf("handling client %s/%d\n", clntName, ntohs(clntAddr.sin_port));
	else puts("unable to get client address");

	HandleTCPClient(clntSock);
    }

    // NOT REACHED
}
