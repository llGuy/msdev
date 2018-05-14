CXX=g++


OS=$(shell uname)
ifeq ($(OS),Darwin)
	CFLAGS=-std=c++14 -L/usr/local/lib
else
	CFLAGS=-std=c++1z
endif

all: server client

server: serv_main.cpp serv_server.cpp serv_connection.cpp socket.cpp log.cpp
	$(CXX) $(CFLAGS) -o $@ $^ -lpthread

client: cli_client.cpp cli_main.cpp socket.cpp cli_console.cpp log.cpp cli_message.cpp algorithm.cpp 
	$(CXX) $(CFLAGS) -g -o $@ $^ -lncurses 

clean:
	/bin/rm -f client server
