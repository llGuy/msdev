#pragma once
#include <iostream>
#include <string>
#undef cimg_display
#define cimg_display 0
#include "CImg.h"

using namespace cimg_library;
using namespace std;

typedef unsigned char unchar_t;

class LSB_Encoding
{
public:
	LSB_Encoding(string input_string);
	~LSB_Encoding();

	//string that will be encoded into the image
	string _input_str;

	//pointer points to the first pixel of the image
	unchar_t * _pntr_fst_pix;

	//area of the image
	unsigned int _area;

	//number of characters that can be stored in the image
	unsigned int _num_char_pos;

	//changes least important bit of byte to 1 or 0
	unsigned int ModByte(unsigned int byte_of_img, unsigned int bit) const;

	unsigned GetNthBit(unsigned int shifter, unsigned int byte) const;

	//this function writes the _input_str to the image
	void WriteToImage();
};

