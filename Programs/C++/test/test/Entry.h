#pragma once
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include "Encrypt.h"

using namespace std;

class Entry
{
public:
	Entry(string input = "NULL");
	~Entry();
	string _name;
	string _username;
	string _password;
};

