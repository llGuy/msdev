#pragma once
#include "Entry.h"
#include "Encrypt.h"
#include "Vector.h"
#include <iostream>
#include <string>
#include <fstream>
class EntryManager
{
public:
	//directory
	string kFILE = "c:\\Users\\luc\\Documents\\SourceB.txt";

	EntryManager();
	~EntryManager();

	//Adds to the vector, the entries
	void AddEntries(Entry _input);	

	//Adds vector entries to the file
	void UpdateFle();	

	void clearFile();

	//updates passwords to the vector
	void UpdateVector();

	Vector _vec_of_ent;

	//all the name,pwds from the file (decrypted)
	string _outp_fle;
};

