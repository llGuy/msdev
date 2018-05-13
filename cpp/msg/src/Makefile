CC=g++
CFLAGS=-std=c++1z

all: server client

server: serv_main.cpp serv_server.cpp serv_connection.cpp socket.cpp log.cpp
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

client: cli_client.cpp cli_main.cpp socket.cpp cli_console.cpp log.cpp cli_message.cpp algorithm.cpp -lncurses 
	$(CC) $(CFLAGS) -g -o $@ $^
