#pragma once
#include "Entry.h"
#include "Encrypt.h"
#include <iostream>
#include <string>

using namespace std;
class Vector
{
public:
	Vector();
	~Vector();
	int _size;
	string *_str_pwd;
	string _all_str;

	//adds entry to vector
	void addEntry(Entry input);

	//puts all the entries.strComp() together to make 1 string
	void convString();

private:
	Entry *_arr_ent;
	int _capacity;
};

