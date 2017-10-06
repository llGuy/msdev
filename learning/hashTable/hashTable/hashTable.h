#pragma once
#include <iostream>
#include <stdio.h>
#include "vector.h"
#include "item.h"
class hashTable
{
public:
	hashTable(int size = 8);
	~hashTable();
	int _size;
	vector * _arrayOfVectors;
	void addNumber(item _itemInput);
	void PrintItems();
	void findItem(int _itemInput);
};

