#pragma once
#include <stdio.h>
#define NULL 0
class vector
{
public:
	vector();
	~vector();
	int _capacity = 8;
	int _size = 0;
	int * _array;
	void PlaceNum(int _input);
	void PrintAllItems();
	int find(int _input);
};

