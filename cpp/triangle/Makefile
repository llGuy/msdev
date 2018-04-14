LPATH=-L/usr/lib/x86_64-linux-gnu
IPATH=-I/usr/include
CFLAGS=$(IPATH)
CC=g++ $(CFLAGS)
WINCC=i686-w64-mingw32-gcc $(CFLAGS)

linux: main.o window.o
	$(CC) main.o window.o -o output  -lglfw

main.o: src/main.cpp
	g++ -c -std=c++1z src/main.cpp

window.o: src/window.cpp
	g++ -c -std=c++1z src/window.cpp

clean: rm *.o output
