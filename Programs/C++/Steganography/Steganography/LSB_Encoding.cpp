#include "LSB_Encoding.h"



LSB_Encoding::LSB_Encoding(string input_string)
{
	_input_str = input_string;
	CImg<unchar_t> temp("C:\\Users\\luc\\Desktop\\Programs\\C++\\_TtPuzHs.bmp");
	_pntr_fst_pix = temp.data();
	_area = temp.width() * temp.height();
	_num_char_pos = _area / 8;
	
}

unsigned LSB_Encoding::ModByte(unsigned byte_of_img,unsigned bit) const {
	if(bit) {
		byte_of_img |= bit;
		return byte_of_img;
	}
	else {
		bit = 0b11111110;
		byte_of_img &= bit;
		return byte_of_img;
	}
}

void LSB_Encoding::WriteToImage() {
	unchar_t * _arr_bytes = new unchar_t[_input_str.size()];
	for(int i = 0; i < _input_str.size(); i++) {
		for(int x = 7; x >= 0; x--) {
			unsigned _temp = (unsigned)_input_str[i];
			ModByte(_temp, GetNthBit(x, _temp));
		}
	}
}

unsigned LSB_Encoding::GetNthBit(unsigned shifter, unsigned byte)const {
	return (byte>>shifter)%2;
}

LSB_Encoding::~LSB_Encoding()
{
}
