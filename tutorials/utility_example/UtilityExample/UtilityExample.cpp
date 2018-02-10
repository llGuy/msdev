// UtilityExample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char*argv[])
{
	//ofstream of("hello.txt");
	//cout << "argc=" << argc << endl;
	cout << "wrote to hello.txt" << endl;
	if ((string)argv[1] == "hello") {
		cout << "Got hello" << endl;
	}
	for (int i = 0; i < argc; i++) {
		cout << "argv[" << i << "]=" << (const char*)argv[i] << endl;
	}
    return 0;
}

