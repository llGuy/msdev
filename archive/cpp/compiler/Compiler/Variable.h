#pragma once
#include <iostream>
template <class Type> class Variable {
public:
	Variable() {
		_name = "NULL";
		isEndOfList = false;
	}
	Variable(Type value, std::string inputName){
		_value = value;
	}
	~Variable(){
		delete _pointerNextVar;
	}
	std::string _name;
	Type _value;
	Variable<Type> * _pointerNextVar;
	bool isEndOfList;
	void operator=(Type other) {
		_value = other;
	}
	friend std::ostream &operator<<(std::ostream &stream, Variable<Type> &inputVariable) {
		stream << inputVariable._value;
		return stream;
	}
};
