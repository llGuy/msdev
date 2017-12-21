#include <iostream>

#include "compiler/Compiler.h"
#include "hint/hints.h"

const bool g_TEST1 = true;
const bool g_TEST2 = false;

int main(int argc,char* argv[]) {
	//if(g_TEST1) argv[1] = "-t";
	//if(g_TEST2) argv[1] = "-h";

	std::vector<std::string> l_vecParams;
	for(int l_iter = 0; l_iter < argc; ++l_iter)
		l_vecParams.push_back(argv[l_iter]);

	//gives clues as to how to use
	//the language
	if(l_vecParams[1] == "-h") {
		std::cout << "in here" << std::endl;
		G_GiveHints(l_vecParams[2]);
	}
	//runs a program
	else if(l_vecParams[1] == "-r") {
		std::fstream l_file;
		l_file.open(l_vecParams[2]);
		sw_lang::cmpl::Compiler l_comp(l_file);
		l_file.close();
		l_comp.M_ExecuteInstrs();
	}
	//tests if instructions work
	else if(l_vecParams[1] == "-t") {
		std::fstream l_file;
		std::string l_dir = "C:\\Users\\luc\\Documents\\Visual Studio 2017\\Projects\\SW-Language\\SW-Language\\test-programs\\test1.txt";
		l_file.open(l_dir);
		sw_lang::cmpl::Compiler l_comp(l_file);
		l_file.close();
		l_comp.M_ExecuteInstrs();
	}
	return 0;
}