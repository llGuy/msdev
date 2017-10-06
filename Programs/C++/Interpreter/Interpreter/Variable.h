#pragma once
#include <iostream>
//actual variable class that will be stored in llists
template <class Type> 
class Variable {
public:
	//if the variable is not initialized
	//compiler sets it's name to "NULL"
	explicit Variable(void) {
		_name = "NULL";
		isEndOfList = false;
	}
	explicit Variable(Type value,const std::string &inputName) 
		: _value(value) 
	{
	}
	~Variable(void) {delete _pointerNextVar;}
	//contains the name of the variable given by the user
	std::string _name;
	//ONLY FOR STRINGS
	//checks if the string has been encrypted
	bool _isEncrypted = false;

	//	ACTUAL VALUE OF THE VARIABLE
	Type _value;

	//for llist
	Variable<Type>* _pointerNextVar;
	//is at the end of the list
	bool isEndOfList;
	void operator=(Type other) {_value = other;}
	friend std::ostream &operator<<(std::ostream &stream,Variable<Type> &inputVariable) {
		stream << inputVariable._value;
		return stream;
	}
};
