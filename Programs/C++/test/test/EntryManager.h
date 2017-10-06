#pragma once
#include <iostream>
#include <stdio.h>
#include <fstream>
#include "Entry.h"
#include "Encrypt.h"

class EntryManager
{
public:
	EntryManager();
	~EntryManager();
	bool Introduction();
	void Compile();
	void Add();
};

