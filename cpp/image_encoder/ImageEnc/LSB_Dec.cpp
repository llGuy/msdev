#include "LSB_Dec.h"
#include "CImg.h"

#undef cimg_display
#define cimg_display 0

using namespace cimg_library;

static CImg<unchar_t> i_image("C:\\Users\\luc\\Desktop\\Programs.OLD\\C++\\_TtPuzHsCOPY.bmp");
//static CImg<unchar_t> i_image("C:\\Users\\luc\\Desktop\\Programs.OLD\\C++\\IMGd.bmp");

LSB_Dec::LSB_Dec()
{
	//first_pixel corresponds to a pointer that points to the first pixel of the image
	_first_pixel = i_image.data();
}

unsigned LSB_Dec::GetBit(unchar_t _i_byte)
{
	//gets the least significant bit 
	return ((unsigned)_i_byte) % 2;
}

unsigned LSB_Dec::GetNthBit(unsigned i_byte,unsigned i_shifter)const
{
	//returns the "shifter"th bit of i_bytel
	return (i_byte>>i_shifter)%2;
}

void LSB_Dec::AddVector(unsigned _i_bit)
{
	//add to a vector, a bit
	_vec_of_bits.push_back(GetBit((unchar_t)_i_bit));
}

void LSB_Dec::ReadImg()
{
	//zero_counter counts the streak of zero
	//if the streak is at 8 i.e. 0b00000000, the while loop will stop
	unsigned _zero_counter = 0;

	//counter of bits
	unsigned _counter = 0;
	bool _continue = true;

	//will be used to structure a byte
	unsigned _temp = 0;

	while(_continue==true) {
		if(_zero_counter == 8) {						//if streak has reached goal
			_continue = false;							//stop the loop
			break;
		}
		else {
			if(GetBit(_first_pixel[_counter])==0) {				//if bit = 0, add to zero_counter
				_zero_counter++;
			}
			else {
				//breaks the streak
				_zero_counter = 0;

				//edit _temp
				unsigned _add_on = (1 << (7-(_counter % 8)));
				_temp = _temp + _add_on;
			}
			if(_counter) {
				//if counter = 0
				if(_counter % 8 == 0) {
					//add temp to the vector
					_num_to_conv.push_back(_temp);
					//set _temp back to 0
					_temp = 0;
				}
			}
			_counter++;
		}
	}
	for(int i = 0; i < _num_to_conv.size(); i++) {
		_dec_str += (char)_num_to_conv[i];
	}
}

LSB_Dec::~LSB_Dec()
{
}
