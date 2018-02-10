#pragma once
#include <iostream>
#include <string>

typedef unsigned char unchar;

using namespace std;	
class SCR_Decoder
{
public:
	SCR_Decoder(string i_code);
	~SCR_Decoder();
	string _input_code;
	string _output_str = "";
	string _order_str = "0000";
	unsigned _arr_order[8];
	unsigned _size_code;

	string DecodeInput();
	string BinaryConverter(unchar i_unchar);
	unchar UnscrambleBits(unchar i_unchar);
	unsigned ShiftBits(unchar i_unchar,unsigned i_shifter);
	void FindOrder();
	void PrintDebugger();
	unsigned Power(unsigned _int, unsigned _exp);
};

