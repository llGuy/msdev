#include <iostream>
#include <stdio.h>
#include "vector.h"
#include "hashTable.h"

using namespace std;

int main() {
	hashTable hash = 32;
	item theItem = 342;
	item anItem = 816;
	item arrayOfStuffs[1000];
	for(int i = 0; i < 1000; i++) {
		arrayOfStuffs[i] = i + 100;
		hash.addNumber(arrayOfStuffs[i]._inputNum);
	}
	hash.addNumber(theItem);
	hash.addNumber(anItem);
	hash.PrintItems();
	hash.findItem(123);
	cout << endl;
	int i = 10;
	cout << sizeof(i) <<endl;
}