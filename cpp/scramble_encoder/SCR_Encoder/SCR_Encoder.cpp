#include "SCR_Encoder.h"

SCR_Encoder::SCR_Encoder(string i_input)
{
	_input_str = i_input;
	_output_str = _input_str;
	_size_input_str = _input_str.length();
	for (unsigned _pos = 0; _pos < 4; _pos++)
	{
		_arr_order_str[_pos] = char(0b00000000);
	}
}

void SCR_Encoder::DefineArrOrder(string i_order)
{
	for (unsigned _pos = 0; _pos < 8; _pos++)
	{
		_arr_order[_pos] = unsigned(i_order[_pos]) - 48;
	}
}

string SCR_Encoder::EncodeInput()
{
	for (unsigned _nth_letter_input = 0; _nth_letter_input < _size_input_str; _nth_letter_input++)
	{
		_output_str[_nth_letter_input] = ScrambleInput(_input_str[_nth_letter_input]);
	}

	STRGenerateOrder();
	return _output_str;
}

unchar SCR_Encoder::ScrambleInput(unchar i_unchar)
{
	unchar _new_char = 0b00000000;
	unsigned _arr_bits_i_unchar[8];
	for (unsigned _nth_bit = 0; _nth_bit < 8; _nth_bit++)
	{
		unchar _temp = i_unchar;
		_arr_bits_i_unchar[_nth_bit] = ShiftBits(_temp, 7 - _nth_bit) % 2;
	}
	for (unsigned _nth_bit = 0; _nth_bit < 8; _nth_bit++)
	{
		if (_arr_bits_i_unchar[_nth_bit] == 1) {
			_new_char += Power(2, 7 - _arr_order[_nth_bit]);
			unsigned _temp = unsigned(_new_char);
		}
	}
	return _new_char;
}

string SCR_Encoder::BinaryConverter(unchar i_unchar)
{
	string _temp = "00000000";
	for (unsigned _instance = 0; _instance < 8; _instance++)
	{
		_temp[_instance] = ShiftBits(i_unchar, 7 - _instance) % 2 + 48;
	}
	return _temp;
}

unsigned SCR_Encoder::ShiftBits(unchar i_unchar, unsigned i_shifter)
{
	return i_unchar >> i_shifter;
}

void SCR_Encoder::STRGenerateOrder()
{
	for (unsigned _pos_order = 0; _pos_order < 8; _pos_order++)
	{
		if (_pos_order % 2 == 0) {
			_arr_order_str[_pos_order / 2] = _arr_order[_pos_order] << 4;
		}
		else {
			_arr_order_str[_pos_order / 2] += _arr_order[_pos_order];
			_output_str += _arr_order_str[_pos_order/2];
		}
	}
}

void SCR_Encoder::PrintDebugger()
{
	cout << "Text to encrypt: " << _input_str << endl;
	cout << "Order of the bits: ";
	for(unsigned _pos_order = 0; _pos_order < 8; _pos_order++)
	{
		cout << _arr_order[_pos_order];
	}
	cout << "\n\nConversion of the bytes:\n";
	for(unsigned _pos_str = 0; _pos_str < _input_str.length(); _pos_str++)
	{
		cout << _input_str[_pos_str] << ": " <<BinaryConverter(_input_str[_pos_str]) << " -> " << _output_str[_pos_str] << ": " <<BinaryConverter(_output_str[_pos_str]) << endl;
	}
	cout << "\n\nThe values of the order: \n";
	for(unsigned _pos_order = 0; _pos_order < 4; _pos_order++)
	{
		cout << BinaryConverter(_arr_order_str[_pos_order]) << " " << _arr_order_str[_pos_order] <<endl;
	}
	cout << "\nThe encrypted string: " << _output_str << endl;
	cout << "\nSUCCESS!\n\n";
}

unsigned SCR_Encoder::Power(unsigned _int, unsigned _exp)
{
	//_result refers to the answer of the operation
	unsigned _result;
	//checks if the exponant is larger than 1
	if (_exp > 1) {
		//Multiplies the number _nth_mult times to get the power
		for (unsigned _nth_mult = 1; _nth_mult < _exp; _nth_mult++)
		{
			_int *= 2;
		}
		_result = _int;
		return _result;
	}
	//Checks  if the exponant is = 1, if so, _int stays the same
	else if (_exp == 1) {
		return _int;
	}
	//If the exponant is = 0, returns 1
	else {
		return 1;
	}
}

SCR_Encoder::~SCR_Encoder()
{
}
