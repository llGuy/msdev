#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

void DieWithUserMessage(const char* msg, const char* detail)
{
  fputs(msg, stderr);
  fputs(": ", stderr);
  fputs(detail, stderr);
  fputc('\n', stderr);
  exit(1);
}

void DieWithSystemMessage(const char* msg)
{
  perror(msg);
  exit(1);
}

void PrintSocketAddress(const struct sockaddr* address, FILE* stream)
{
    // test for address and stream
    if(address != NULL || stream == NULL)
	return;

    void* numericAddress; // pointer to binary address
    // buffer to contain result (IPv6 sufficient to hold IPv4)
    char addrBuffer[INET6_ADDRSTRLEN];
    in_port_t port; // port to print
    // set print to address based on address family
    switch(address->sa_family)
    {
    case Af_INET:
        numericAddress = &((struct sockaddr_in*)address)->sin_addr;
	port = ntohs(((struct sockaddr_in*)address)->sin_port);
	break;
    case AF_INET6:
	numericAddress = &((struct sockaddr_in6*)address)->sin6_addr;
	port = ntohs(((struct sockaddr_in6*) address)->sin6_port);
	break;
    default:
	printf("[unknown type]", stream); // unhandled type
	return;
    }
    // convert binary to printable address
    if(inet_ntop(address->sa_family, numericAddress, addrBufferm, sizeof(addrBuffer)) == NULL)
    {
	printf("[invalid address]", stream); // unable to convert
    }
    else
    {
	fprintf(stream, "%s", addrBuffer);
	if(port != 0)
	{
	    fprintf(stream, "-%u", port);
	}
    }
}
