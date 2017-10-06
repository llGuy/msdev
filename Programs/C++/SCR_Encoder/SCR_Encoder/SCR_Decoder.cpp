#include "SCR_Decoder.h"

SCR_Decoder::SCR_Decoder(string i_code)
{
	_input_code = i_code;
	cout << _input_code[0] << endl;
	_size_code = _input_code.length();
	for(unsigned _input_pos = 0; _input_pos < _input_code.length() - 4; _input_pos++)
	{
		_output_str = _output_str + char(0b00000000);
	}
}
void SCR_Decoder::FindOrder()
{
	for(unsigned _order_pos = 0; _order_pos < 8; _order_pos++)
	{
		if(_order_pos % 2 == 0) {
			_arr_order[_order_pos] = _input_code[(_order_pos / 2 + _size_code) - 4] >> 4;
		}
		else {
			char _temp = _input_code[(_order_pos / 2 + _size_code - 4)] << 4;
			_arr_order[_order_pos] = _temp >> 4;
		}
	}
}

string SCR_Decoder::DecodeInput()
{
	FindOrder();
	for(unsigned _input_pos = 0; _input_pos < _input_code.length() - 4; _input_pos++)
	{
		_output_str[_input_pos] = UnscrambleBits(_input_code[_input_pos]);
	}
	return _output_str;
}

unchar SCR_Decoder::UnscrambleBits(unchar i_unchar)
{
	unchar _new_char = 0b00000000;
	unsigned _arr_bits_i_unchar[8];
	for(unsigned _nth_bit = 0; _nth_bit < 8; _nth_bit++)
	{
		unchar _temp = i_unchar;
		_arr_bits_i_unchar[_nth_bit] = ShiftBits(_temp,7 - _nth_bit) % 2;
	}
	for(unsigned _nth_bit = 0; _nth_bit < 8; _nth_bit++)
	{
		if(_arr_bits_i_unchar[_nth_bit] == 1) {
			_new_char += Power(2,7 - _arr_order[_nth_bit]);
		}
	}
	return _new_char;
}


string SCR_Decoder::BinaryConverter(unchar i_unchar)
{
	string _temp = "00000000";
	for(unsigned _instance = 0; _instance < 8; _instance++)
	{
		_temp[_instance] = ShiftBits(i_unchar,7 - _instance) % 2 + 48;
	}
	return _temp;
}

unsigned SCR_Decoder::ShiftBits(unchar i_unchar,unsigned i_shifter)
{
	return i_unchar >> i_shifter;
}

void SCR_Decoder::PrintDebugger()
{
	cout << "Code: " <<_input_code << "\n\n";
	cout << "Order: ";
	for(unsigned _order_pos = 0; _order_pos < 8; _order_pos++)
	{
		cout << _arr_order[_order_pos] << " ";
	}
	cout << endl;
	cout << "Binary value of each char: " << endl;
	for(unsigned _code_pos = 0; _code_pos < _input_code.length() - 4; _code_pos++)
	{
		cout << _input_code[_code_pos] << ": " << BinaryConverter(_input_code[_code_pos]);
		cout << endl;
	}
	cout << endl;
}

unsigned SCR_Decoder::Power(unsigned _int,unsigned _exp)
{
	//_result refers to the answer of the operation
	unsigned _result;
	//checks if the exponant is larger than 1
	if(_exp > 1) {
		//Multiplies the number _nth_mult times to get the power
		for(unsigned _nth_mult = 1; _nth_mult < _exp; _nth_mult++)
		{
			_int *= 2;
		}
		_result = _int;
		return _result;
	}
	//Checks  if the exponant is = 1, if so, _int stays the same
	else if(_exp == 1) {
		return _int;
	}
	//If the exponant is = 0, returns 1
	else {
		return 1;
	}
}

SCR_Decoder::~SCR_Decoder()
{
}

