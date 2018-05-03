output: main.o typing_test.o
	g++ main.o typing_test.o -o typingtest

main.o: main.cpp
	g++ -c -std=c++1z main.cpp

typing_test.o: typing_test.cpp type_test.h
	g++ -c -std=c++1z typing_test.cpp

clean: rmm *.o typingtest
