#pragma once
#include "EntryManager.h"
class Compiler
{
public:
	Compiler();
	~Compiler();
	typedef enum _decision {
		check = 1,
		add = 2,
		clean = 3,
		deletepwd = 4
	};

	//Deletes entries
	void deleteEntry();

	//Deletes content that is in the file
	void deleteContent();

	//Compiles everything and puts it all together
	void Compile();

//private:
	EntryManager EntMAnager;
	int FirstQuestion();

	//Add pwd function
	void Add();
	
	//Check pwd function
	void Check();
};

