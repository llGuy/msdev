#include "vector.h"
#define NULL 0


vector::vector()
{
	_array = new int[_capacity];
	for(int i = 0; i < _capacity; i++) {
		_array[i] = NULL;
	}
}
int vector::find(int _input) {
	return _array[_input];
}
void vector::PlaceNum(int _input) {
	if(_size == _capacity) {
		_capacity = _capacity * 2;
		int * _temp = new int[_capacity];
		for(int i = 0; i < _capacity / 2; i++) {
			_temp[i] = _array[i];
		}
		delete[] _array;
		for(int i = _capacity / 2; i < _capacity; i++) {
			_temp[i] = NULL; 
		}
		_array = _temp;
	}
	if(_size <= _capacity - 1) {
		_array[_size] = _input;
		_size++;
	}
}
void vector::PrintAllItems() {
	for(int i = 0; i < _capacity; i++) {
		printf("%i , ", _array[i]);
	}
}
vector::~vector()
{
	delete[] _array;
}
