#pragma once
#include <iostream>
#include <string>
#include "Misc.h"
#include "Vector.h"
#include "VLists.h"
#include "Parser.h"

//FUNDAMENTAL HEADER OF THE PROGRAM
//RSValue = right-side value

//4 types of RSValues

//RSVConst = constant e.g. 12, 'a', true
//RSVVariable = variable e.g. foo, bar
//RSVOperator = operator e.g. 12 + 3, 54 * (3 -2) / 4	//only for integers
//RSVString = string e.g. "hello world"

template<class T> class RSVConst {
protected:
	typedef T(RSVConst<T>::*func)(void);
	std::string _rsvConst;
	size_t _possibility;
private:
	//depending on the type of the variable, one of these functions will get called
	T FunctionInt(void) {
		int _integer = 0;
		for(size_t _index = 0; _index < _rsvConst.length(); _index++)
			_integer += (int)(_rsvConst[_index] - 48) * Power(10,_rsvConst.length() - _index - 1);
		return _integer;
	}
	T FunctionChar(void) { return _rsvConst[1]; }
	T FunctionBool(void) {
		if(_rsvConst == "true") return true;
		if(_rsvConst == "false") return false;
		else return false;
	}
public:
	T _result;
	//array of function pointers
	//and call the "possibility"th function
	func _arrayOfFunctions[3];
	explicit RSVConst(void) {};
	RSVConst(const std::string &rsv, size_t pos) 
		: _rsvConst(rsv), _possibility(pos) {
		_arrayOfFunctions[0] = &RSVConst<T>::FunctionInt;
		_arrayOfFunctions[1] = &RSVConst<T>::FunctionChar;
		_arrayOfFunctions[2] = &RSVConst<T>::FunctionBool;
	}
	~RSVConst(void) 
	{
	}
	//translate function will return the value of the RSV
	T Translate(void) { return (*this.*_arrayOfFunctions[_possibility])(); };
};

template<class T> class RSVVariable {
private:
	typedef T(RSVVariable::*func)(void);
	std::string _nameOfVariable;
protected:
	//same concept as the previous RSV
	T FunctionInt(void) { return VList::listInt.FindNodeStr(_nameOfVariable,VList::listInt._head)->_value; }
	T FunctionChar(void) { return VList::listChar.FindNodeStr(_nameOfVariable,VList::listChar._head)->_value; }
	T FunctionBool(void) { return VList::listBool.FindNodeStr(_nameOfVariable,VList::listBool._head)->_value; }
public:
	size_t _possibility;
	func _arrayOfFunctionPtr[3];
	explicit RSVVariable(std::string name, size_t pos) 
		: _nameOfVariable(name) {
		_possibility = pos;
		_arrayOfFunctionPtr[0] = &RSVVariable::FunctionInt;
		_arrayOfFunctionPtr[1] = &RSVVariable::FunctionChar;
		_arrayOfFunctionPtr[2] = &RSVVariable::FunctionBool;
	};
	~RSVVariable(void) {};
	T Translate(void) { return (*this.*_arrayOfFunctionPtr[_possibility])(); }
};

class RSVOperation {
private:
	std::string _operation;
public:
	//use the class CalcParser 
	//which will parse through an operation and 
	//return the value of the operation
	CalcParser _parser;
	explicit RSVOperation(const std::string &rsv) 
		: _operation(rsv) { _parser._expression = _operation; }
	~RSVOperation(void) 
	{
	}
	unsigned int GetResult(void) { return _parser.Calculate(); };
};


//simple RSVString because the RSVConst had
//conversion problems with the std::string class
class RSVString {
private:
	std::string _string = "";
public:
	explicit RSVString(const std::string &rsv) 
		: _string(rsv) {};
	~RSVString(void) {};
	std::string Translate(void) {
		std::string _temp = "";
		size_t _index = 1;
		while(_string[_index] != '\"') {
			_temp += _string[_index];
			_index++;
		}
		_string = _temp;
		return _string;
	}
};