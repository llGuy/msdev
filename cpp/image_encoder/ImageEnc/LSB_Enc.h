#include "CImg.h"
#include <iostream>
#include <string>
#pragma once

#undef cimg_display
#define cimg_display 0

using namespace cimg_library;
using namespace std;

typedef unsigned char unchar_t;

//CImg<unchar_t> i_image("C:\\Users\\luc\\Desktop\\Programs.OLD\\C++\\_TtPuzHs.bmp");

class LSB_Enc
{
public:
	LSB_Enc(string i_str);
	~LSB_Enc();
	void EncSequence();
	unsigned GetNthBit(unsigned i_byte, unsigned i_shifter)const;
	unsigned ModByte(unsigned i_byte, unsigned i_bit)const;			//this function works
private:
	unchar_t *_first_pixel;
	unchar_t * _arr_pix;
	CImg<unchar_t> *_p_i_image;
	string _str_enc;
	unsigned _img_size;
};

