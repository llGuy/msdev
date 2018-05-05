SRC_SRV=serv_main.cpp serv.cpp
OBJ_SRV=$(SRC_SRV:.cpp=.o)

bin/msg_server: obj/$(OBJ_SRV)
	g++ -o bin/msg_server $@

obj/%.o: src/%.cpp
	g++ -c $< $@
