#include "Vector.h"



Vector::Vector()
{
	_capacity = 8;
	_size = 0;
	_arr_ent = new Entry[_capacity];
		
}

void Vector::addEntry(Entry input)
{
	if(_size != _capacity)
	{
		//checks if it is possible to add an entry, making sure it isn't full
		_arr_ent[_size] = input;
		_size++;
	}
	else {
		//if it is filled up, multiplies capacity of the vector by 2
		Entry *_arr_temp = new Entry[_capacity*2];
		for(int _pos = 0; _pos < _capacity; _pos++)
		{
			//adds all previous data into the new upgraded array
			_arr_temp[_pos] = _arr_ent[_pos];
		}
		delete[] _arr_ent;
		_arr_ent = _arr_temp;
	}
}

void Vector::convString()
{
	//creates array of strings
	 _str_pwd = new string[_size];
	for(int _pos = 0; _pos < _size; _pos++)
	{
		_str_pwd[_pos] = _arr_ent[_pos].strComp();
		_all_str += _str_pwd[_pos];
	}
}

Vector::~Vector()
{
}
