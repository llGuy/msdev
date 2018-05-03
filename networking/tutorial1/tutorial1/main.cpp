#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <Windows.h>

namespace
{

	SOCKET sock;		// this is the socket that we will use
	SOCKET sock2[200];	// this is the socket that will be recieved from the Clients and sended to them
	SOCKADDR_IN iSock2; // this will contain informations about the clients connected to the server
	SOCKADDR_IN iSock;	// this will contain some informations about our socket
	WSADATA data;		// this is to save our socket version
	int clients = 0;	// we will use it in the accepting clients

}

int StartServer(int port)
{
	int err;
	// to initialize the socket and set out socket version
	// MAKEWORD(2, 2) version 2.2
	// &data is to save the socket version
	WSAStartup(MAKEWORD(2, 2), &data);
	// socket() is to set socket types
	// AF_INET is for IPv4		AF_INET6 is for IPv6
	// SOCK_STREAM is the type stream of the socket (socket that provides a sequence), there are 3
	// other types such as : SOCK_DGRAM, SOCK_RAW...
	// 0 : is the protocol, we have choosed 0(NULL) so that it will automatically use the UDP port, you can put (IPROTO_UDP[UDP Port], 
	// IPROTO_TCP[TCP Port],...)
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		Sleep(4000);
		exit(0);
		return 0;
	}
	iSock.sin_family = AF_INET;
}

int main(void)
{
	

	return 0;
}