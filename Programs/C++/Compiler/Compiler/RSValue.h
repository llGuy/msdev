#pragma once
#include <iostream>
#include <string>
#include "Miscellaneous.h"
#include "Vector.h"
#include "VarLists.h"
#include "CalcParsing.h"

//class to define the value that comes after the = in a declaration, initialization etc..
class RSValue {			//R = right, S = side : Right Side Value
public:
	RSValue() {}
	//string of what is after '='
	std::string _rsValue;
	RSValue(std::string rs_value) { _rsValue = rs_value; }
	~RSValue() {}
	//pure virtual function that will translate _rsValue to C++
	virtual void Translate(std::string name) {}
};
//class to evaluate whether what is after the = is a variable
class RSVVar : public RSValue {
private:
	const std::string TYPE_STR[4] = {"int","char","bool","string"};
	typedef void(RSVVar::*func_type_app)(std::string);
	func_type_app _appendType[4];
	void AppendInt(std::string nameOfVar) {
		VList::listInt.AppendInitializedVariable(VList::listInt.FindNodeStr(_rsValue,VList::listInt._head)->_value,nameOfVar);
	}
	void AppendChar(std::string nameOfVar) {
		VList::listChar.AppendInitializedVariable(VList::listChar.FindNodeStr(_rsValue,VList::listChar._head)->_value,nameOfVar);
	}
	void AppendBool(std::string nameOfVar) {
		VList::listBool.AppendInitializedVariable(VList::listBool.FindNodeStr(_rsValue,VList::listBool._head)->_value,nameOfVar);
	}
	void AppendString(std::string nameOfVar) {
		VList::listStr.AppendInitializedVariable(VList::listStr.FindNodeStr(_rsValue,VList::listStr._head)->_value,nameOfVar);
	}
	std::string _typeOfVar;
	
	void CheckLLST_Fetch_Append(std::string nameOfVar) {
		for(size_t _index = 0; _index < 4; _index++) {
			if(_typeOfVar == TYPE_STR[_index]) (*this.*_appendType[_index])(nameOfVar);
		}
	}
public:
	RSVVar(std::string inputRSV, std::string type) { 
		_rsValue = inputRSV; 
		_typeOfVar = type;
		_appendType[0] = &RSVVar::AppendInt;
		_appendType[1] = &RSVVar::AppendChar;
		_appendType[2] = &RSVVar::AppendBool;
		_appendType[3] = &RSVVar::AppendString;
	}
	~RSVVar() {}
	virtual void Translate(std::string name) {
		CheckLLST_Fetch_Append(name);
	}
};
//class to evaluate whether what is after the = is a constant
//such as 4, 'a', "foo", true
class RSVConst : public RSValue {
private:
	//this is the length of the right side string
	unsigned int _rsValLength;
	//the value of the letter if there is one
	char _rsLetter;
	//value of the int if there is one
	unsigned int _rsNumber = 0;
	//value of the boolean if there is one
	bool _rsBool = false;

	//will return true if the RSValue is a char
	bool FindLetter() {
		if(_rsValue[0] == '\'') {
			_rsLetter = _rsValue[1];
			return true;
		}
		return false;
	}
	//will return true if the RSValue is an int
	bool FindNumber() {
		bool _isInt = false;
		for(int _integer = 0; _integer < 10; _integer++) {
			if((int)_rsValue[0] - 48 == _integer) {
				_isInt = true;
				break;
			}
		}
		if(_isInt == false) return false;
		_rsValLength = _rsValue.length();
		for(unsigned _digit = 0; _digit < _rsValLength; _digit++) 
			_rsNumber += (int)(_rsValue[_digit] - 48) * Power(10,_rsValLength - _digit - 1);
		_arrPossibilities[1] = true;
		return true;
	}
	//function to check for boolean
	bool FindBool() {
		if(_rsValue == "true") {
			_arrPossibilities[2] = true;
			_rsBool = true;
			return true;
		}
		else if(_rsValue == "false") {
			_arrPossibilities[2] = true;
			_rsBool = false;
			return true;
		}
		else return false;
	}
public:
	inline static unsigned int CalculateStrTOInt(std::string inputValue) {
		unsigned int _lengthOfNum = inputValue.length();
		unsigned int _result = 0;
		for(unsigned int _digitOfNum = 0; _digitOfNum < _lengthOfNum; _digitOfNum++)
			_result += (int)(inputValue[_digitOfNum] - 48) * Power(10, _lengthOfNum - _digitOfNum - 1);
		return _result;
	}
	RSVConst(std::string rs_value) { _rsValue = rs_value; }
	~RSVConst() {}
	//one of these will be true
	bool _arrPossibilities[3] ={
		false, false, false			//char, int, bool
	};
	virtual void Translate(std::string name) {
		if(FindLetter()) VList::listChar.AppendInitializedVariable(_rsLetter,name);
		else if(FindNumber()) VList::listInt.AppendInitializedVariable(_rsNumber,name);
		else if(FindBool()) VList::listBool.AppendInitializedVariable(_rsBool, name);
	}
};
//class to evaluate if the RSValue is an operation
//such as: 4 + 5, x + 12 etc..
class RSVOperation : public RSValue {
public:
	CalcParser _parser;
	RSVOperation(std::string rsv) { 
		_rsValue = rsv; 
		_parser._expression = rsv;
	}
	~RSVOperation() {}
	virtual void Translate(std::string name) {
		VList::listInt.AppendInitializedVariable(_parser.Calculate(),name);
	}
};
//class to evaluate if the RSVale is a string
class RSVString : public RSValue {
public:
	std::string _rsValueOriginal;
	std::string _actualRSV;
	RSVString(std::string rsValue) { _rsValueOriginal = rsValue; }
	~RSVString(){}
	virtual void Translate(std::string name) {
		unsigned int _index = 1;
		while(_rsValueOriginal[_index] != '\"') {
			_actualRSV += _rsValueOriginal[_index];
			_index++;
		}
		VList::listStr.AppendInitializedVariable(_actualRSV, name);
	}
};

