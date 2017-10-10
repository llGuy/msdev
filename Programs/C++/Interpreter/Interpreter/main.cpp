#include "Tests.h"
#include "Program.h"
#include <fstream>
#include <iostream>

#define TESTING 0

//set PATH=%PATH%;C:\Users\luc\Development\msdev\Programs\C++\Interpreter\Debug

int main(int argc,char* argv[]) {
#if TESTING
	Test test;
	test.Run();
#else
	std::fstream fileReadFrom;
	//argv[1] = "C:\\Users\\luc\\Desktop\\program.txt";
	fileReadFrom.open("program.txt");

	Program programToExecute(fileReadFrom);
	programToExecute.ExecuteProgram();
	fileReadFrom.close();
#endif
	return 0;
}