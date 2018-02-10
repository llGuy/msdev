#include "Entry.h"



Entry::Entry(string name, string password)
{
	_name = name;
	_pwd = password;
}

string Entry::strComp()
{
	//formats the string as name,pwd;
	return _name + "," + _pwd + ";";
}

Entry::~Entry()
{
}
