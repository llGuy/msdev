#include <iostream>
#include <string>
#include "SCR_Encoder.h"
#include "SCR_Decoder.h"

#define BOOL 1

using namespace std;

int main()
{
	if(BOOL) {
		SCR_Encoder Encoder = "b";
		Encoder.DefineArrOrder("70615243");
		string thing = Encoder.EncodeInput();
		Encoder.PrintDebugger();
	}
	else {
		SCR_Decoder Decoder = "èpaRC";
		cout << Decoder.BinaryConverter(Decoder._input_code[0]);
		Decoder.FindOrder();
		Decoder.PrintDebugger();
		//Decoder.PrintDebugger();
		string temp2 = Decoder.DecodeInput();
		//for(int i = 0; i < 8; i++)
		//{
		//	cout << Decoder._arr_order[i] << endl;
		//}
	}
	//cout << thing.length() << endl;
	//for (int i = 0; i < thing.length(); i++){
	//	cout << i << ": " << Encoder.BinaryConverter(thing[i]) << " " << thing[i]<< endl;
	//}
}
	