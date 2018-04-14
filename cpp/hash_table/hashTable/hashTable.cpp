#include "hashTable.h"
#include <iostream>
#include <string>
using namespace std;


hashTable::hashTable(int size){
	_size = size;
	_arrayOfVectors = new vector[_size];
}

void hashTable::addNumber(item _itemInput) {
	_arrayOfVectors[_itemInput._inputNum % _size].PlaceNum(_itemInput._inputNum);
}

void hashTable::PrintItems() {
	for(int i = 0; i < _size; i++) {
		printf("[%i] = %i elements : ",i,_arrayOfVectors[i]._size);
		_arrayOfVectors[i].PrintAllItems();
		printf("\n\n\n");
	}
}

void hashTable::findItem(int _itemInput) {
	bool _found = true;
	int _tempSize = 0;
	while(_found == true) {
		if(_arrayOfVectors[_itemInput % _size].find(_tempSize)==_itemInput) {
			cout << (_itemInput % _size)+1 << "." << _tempSize+1 << endl;
			_found = false;
			break;
		}
		else if(_tempSize == _arrayOfVectors[_itemInput % _size]._capacity - 1) {
			printf("%i doesn't exist\n",_itemInput);
			_found = false;
			break;
		}
		else {
			++_tempSize;
		}
	}
}

hashTable::~hashTable(){

}
