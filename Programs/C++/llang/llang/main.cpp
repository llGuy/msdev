//contains include statements for lib
//#include "Misc.h"

#include "Test.h"
#include "HTable.h"
#include "VarHTables.h"
#include "RSV_Variable.h"

#include "IncludeCLine.h"

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
		Test test;
		test.PerformTest();
	#endif
#else 
	//not in testing mode
#endif
}