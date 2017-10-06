#pragma once
#include <iostream>

template <class Type> class Vector {
public:
	Type * _arrOfType;
	unsigned int _capacity = 8;
	unsigned int _size = 0;

	void PushBack(Type inputToPush) {
		if(_size == _capacity) {
			_capacity *= 2;
			Type * _arrTemp = new Type[_capacity];
			for(unsigned int _index = 0; _index < _size; _index++) _arrTemp[_index] = _arrOfType[_index];
			delete[] _arrOfType;
			_arrOfType = _arrTemp;
		}
		if(_size < _capacity) {
			_arrOfType[_size] = inputToPush;
			_size++;
		}
	}
	Type operator[] (int index) {
		return _arrOfType[index];
	}
	Vector() { _arrOfType = new Type[_capacity]; }
	~Vector() {}
};