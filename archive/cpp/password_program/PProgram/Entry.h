#pragma once
#include <iostream>
#include <string>

using namespace std;

class Entry
{
public:
	Entry(string name = "Null", string password = "Null");
	~Entry();
	string _name;
	string _pwd;

	//puts name pwd together in 1 string
	string strComp();
};

