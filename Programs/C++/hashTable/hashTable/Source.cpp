#include <iostream>
#include <stdio.h>
#include "vector.h"
#include "hashTable.h"
#define NUMBER 10000

using namespace std;

int main() {
	hashTable hash = 64;
	hash.PrintItems();
	item arrayOfStuffs[NUMBER];
	for(int i = 0; i < NUMBER; i++) {
		arrayOfStuffs[i] = i + 100;
		hash.addNumber(arrayOfStuffs[i]._inputNum);
	}
	hash.PrintItems();
	hash.findItem(1234);
}