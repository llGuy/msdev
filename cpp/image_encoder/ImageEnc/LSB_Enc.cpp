#include "LSB_Enc.h"

#include "CImg.h"

#undef cimg_display
#define cimg_display 0

using namespace cimg_library;

const char * _dir = "C:\\Users\\luc\\Desktop\\Programs.OLD\\C++\\_TtPuzHs.bmp";

static CImg<unchar_t> i_image(_dir);


LSB_Enc::LSB_Enc(string i_str)
{
	//CImg<unchar_t> i_image("C:\\Users\\luc\\Desktop\\Programs.OLD\\C++\\_TtPuzHs.bmp");
	_first_pixel = i_image.data();
	_img_size = i_image.width() * i_image.height();
	_arr_pix = i_image.data();
	_str_enc = i_str;
	
}

unsigned LSB_Enc::ModByte(unsigned i_byte,unsigned i_bit) const
{
	if(i_bit) {
		return i_byte|i_bit;
	}
	else {
		i_bit = 0b11111110;
		return i_byte&i_bit;
	}
}

unsigned LSB_Enc::GetNthBit(unsigned i_byte,unsigned i_shifter)const
{
	return (i_byte>>i_shifter)%2;
}

void LSB_Enc::EncSequence()
{
	//array of all the bits of the string
	unsigned *_arr_bits_of_str = new unsigned[_str_enc.size()*8 + 8];\
	
	int _counter = 0;

	//for loop, cycles through each char of _str_enc (string to get encrypted)
	for(int i = 0; i <_str_enc.size(); i++) {
		//_counter will allow the addition of each it to the _arr_bits_of_str

		//"i"th letter
		char _t_char = _str_enc[i];

		//cycles through each bit of each letter of the _str_enc to complete _arr_bits_of_str
		for(int x = 7; x >= 0; x--) {
			if(x) {
				_arr_bits_of_str[_counter] = GetNthBit((unsigned)_t_char,x);
			}
			else {
				_arr_bits_of_str[_counter] = GetNthBit((unsigned)_t_char,0);
			}
			++_counter;
		}
		if(i == _str_enc.size() - 1) {
			//adds 8 0s at the end to define the end when decrypting
			unsigned _sec_temp = _str_enc.size() * 8;
			for(int e = 0; e < 8; e ++) {
				_arr_bits_of_str[_sec_temp + e] = 0;
			}
		}
	}
	//loop cycles through the bytes of the bmp image to encrypt _str_enc
	for(int i = 0; i < _str_enc.size()*8+8; i++) {
		unchar_t _temp = _arr_pix[i];
		_arr_pix[i] = ModByte((unsigned)_temp,_arr_bits_of_str[i]);
	}
	i_image.save("C:\\Users\\luc\\Desktop\\Programs.OLD\\C++\\_TtPuzHsCOPY.bmp");
}

LSB_Enc::~LSB_Enc()
{
	
}
