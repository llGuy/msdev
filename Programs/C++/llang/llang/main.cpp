//contains include statements for lib
//#include "Misc.h"

#include "Program.h"

#define _TESTING true
#define _FILEIO true

int main(int argc,char* argv[]) {
#if _TESTING
	//in testing mode
	#if _FILEIO
		std::fstream l_fileReadFrom;
		l_fileReadFrom.open("program.txt");

		Program l_programToExecute(l_fileReadFrom);
		l_programToExecute.M_Execute();
		l_fileReadFrom.close();
	#else
		#include "Test.h"
		Test test;
		test.PerformTest();
	#endif
#else 
	std::fstream l_fileRead;
	l_fileRead.open(argv[1]);

	Program l_program(l_fileRead);
	l_program.M_Execute();
	l_fileRead.close();

	std::cin.get();
#endif
}