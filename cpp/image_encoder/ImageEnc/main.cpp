#include "LSB_Dec.h"
#include "LSB_Enc.h"
#include <iostream>
#include <string>
#include <sstream>
#pragma once

#define BOOL 1
#define BOOL_ 1

using namespace std;

int main(int argc, char*argv[])
{
	if(argc > 1) {
		if((string)argv[1] == "-d") {
			LSB_Dec dec_class;
			dec_class.ReadImg();
			cout << dec_class._dec_str << "\n\n";
		}
		else if((string)argv[1] == "-e") {
			string input_str;
			for(int i = 2; i < argc; i++) {
				input_str += argv[i];
				input_str += " ";
			}
			input_str += "\n\n";

			LSB_Enc enc_class = input_str;
			enc_class.EncSequence();
			cout << "success \n\n";
		}
		else {
			cout << "error\n\n";
		}
	}
	else{
		cout << "error\n\n";
	}
	

	return 0;
}
