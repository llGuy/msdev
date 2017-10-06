#pragma once
#include <iostream>
#include <string>

using namespace std;

typedef unsigned char unchar;

class SCR_Encoder
{
public:
	SCR_Encoder(string i_input);
	~SCR_Encoder();
	string _input_str;
	string _output_str;
	string _arr_order_str = "0000";
	unsigned _arr_order[8];
	unsigned _size_input_str;

	void DefineArrOrder(string i_order);
	string EncodeInput();
	unchar ScrambleInput(unchar i_unchar);
	unsigned ShiftBits(unchar i_unchar, unsigned i_shifter);
	void STRGenerateOrder();
	void PrintDebugger();

	unsigned Power(unsigned _int, unsigned _exp);
	string BinaryConverter(unchar i_unchar);
};

