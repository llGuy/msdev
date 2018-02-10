#include "Entry.h"
#include "Encrypt.h"
#include "Vector.h"
#include "EntryManager.h"
#include "Compiler.h"

#include <iostream>
#include <string>

using namespace std;
//const string kFILE = "c:\\Users\\luc\\Desktop\\SourceB.txt";

int main()
{
	if(1) {
		Compiler ProgramCompiler;
		ProgramCompiler.Compile();
	}
	//last lol,lel;
	else {
		if(0) {
			EntryManager test;
			test.UpdateVector();
			test.AddEntries(Entry("computer","processor"));
			test.AddEntries(Entry("piano","chopin"));
			test.UpdateFle();
		}
		else {
			Compiler testComp;
			testComp.Check();
		}
	}
}
