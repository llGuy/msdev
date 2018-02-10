#include <iostream>
#include <string>
#include <vector>
#pragma once

using namespace std;

typedef unsigned char unchar_t;

//CImg<unchar_t> i_image("C:\\Users\\luc\\Desktop\\Programs.OLD\\C++\\_TtPuzHs.bmp");

class LSB_Dec
{
public:
	LSB_Dec();
	~LSB_Dec();
	//finds least important bit of the byte given
	unsigned GetBit(unchar_t _i_byte);
	unsigned GetNthBit(unsigned i_byte,unsigned i_shifter)const;
	void AddVector(unsigned _i_bit);
	void ReadImg();

	vector<unsigned> _vec_of_bits;
	vector<unsigned> _num_to_conv;

	unchar_t *_first_pixel;
	
	//output string which contains encrypted text
	string _dec_str;
};

