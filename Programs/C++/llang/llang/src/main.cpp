//contains include statements for lib
//#include "Misc.h"

#include "parsers/Program.h"


//testing
//#include "cline/func/Def.h"
//#include "cline/func/Call.h
#include "testing/Test.h"

#define _TESTING true
#define _FILEIO false

int main(int argc,char* argv[]) {
#if _TESTING
	//in testing mode
	#if _FILEIO
		std::fstream l_fileReadFrom;
		l_fileReadFrom.open("C:\\Users\\lucro\\Development\\msdev\\Programs\\C++\\llang\\llang\\test-programs\\fizzbuzz.txt");

		Program l_programToExecute(l_fileReadFrom);
		l_programToExecute.M_Execute();
		l_fileReadFrom.close();
	#else
		Test test;
		test.PerformTest();

		std::cin.get();
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