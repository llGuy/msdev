#pragma once
#include <iostream>
#include "Error.h"
#include "VLists.h"

enum type {
	type_int,type_char,type_bool,type_string,type_default
};

//non-significant function used in some of the derived classes of RSValue
inline unsigned int Power(int num,int exp) {
	if(exp == 0) return 1;
	if(exp == 1) return num;
	if(exp > 1) {
		//creates int result
		unsigned int result = 1;
		for(int j = 0; j < exp; j++) {
			//result is multiplied by the original number input
			result = result * num;
		}
		return result;
	}
	else return 1;
}
inline unsigned int FindNumDigits(unsigned int input) {
	unsigned int count = 0;
	while(input != 0) {
		input /= 10;
		count++;
	}
	return count;
}
inline std::string ConvertIntToString(unsigned int num) {
	std::string result;
	unsigned int NumOfDigits = FindNumDigits(num);
	char *arrayOfChar = new char[NumOfDigits];
	for(unsigned int digit = 0; digit < NumOfDigits; digit++) {
		arrayOfChar[digit] = (char)num % 10 + 48;
		num /= 10;
	}
	for(unsigned int digit = NumOfDigits; digit > 0; digit--) {
		result += arrayOfChar[digit - 1];
	}
	return result;
}
inline unsigned int CalculateStrTOInt(const std::string &inputValue) {
	unsigned int _lengthOfNum = inputValue.length();
	unsigned int _result = 0;
	for(unsigned int _digitOfNum = 0; _digitOfNum < _lengthOfNum; _digitOfNum++)
		_result += (int)(inputValue[_digitOfNum] - 48) * Power(10,_lengthOfNum - _digitOfNum - 1);
	return _result;
}
inline bool CheckVar(const std::string &rsv) {
	bool _couldBeVar[] ={ true, false, false, false }; 
	bool _result = true;
	if(rsv == "true"||rsv == "false") _couldBeVar[0] = false;
	if(rsv[0] != '\'') _couldBeVar[1] = true;
	if(rsv[0] != '\"') _couldBeVar[2] = true;
	if((int)rsv[0] < 48 || (int)rsv[0] > 57) _couldBeVar[3] = true;
	for(int _indexCBV = 0; _indexCBV < 4; _indexCBV++)
		_result = _result & _couldBeVar[_indexCBV];
	return _result;
}
//function to get the type of a constant value
//example: the type of 1, 'a' or true
//so that the compiler knows which linked list to look inside
type GetTypeOfConst(const std::string &constItem,type &result) {
	//checking if the value contains what the value
	//of the type should have
	if(constItem == "true"||constItem == "false") 
		result = type_bool;
	else if(constItem[0] == '\'') 
		result = type_char;
	else if(constItem[0] == '\"') 
		result = type_string;
	else if((int)constItem[0] >= 48&&(int)constItem[0] < 58) 
		result = type_int;

	return result;
}
//function works out what type a variable is
//example: what type variable foo is
type GetType(const std::string &nameOfVar,type &result) {
	//will throw exception if the variable doesn't exist
	try {
		//4 lambdas which return boolean of whether the variable exists in 
		//one of the linked lists
		auto _checkInt = [=](void)->bool {
			return nameOfVar == VList::listInt.FindNodeStr(nameOfVar,VList::listInt._head)->_name; };
		auto _checkChar = [=](void)->bool {return nameOfVar == VList::listChar.FindNodeStr(nameOfVar,VList::listChar._head)->_name; };
		auto _checkBool = [=](void)->bool {return nameOfVar == VList::listBool.FindNodeStr(nameOfVar,VList::listBool._head)->_name; };
		auto _checkString = [=](void)->bool {return nameOfVar == VList::listStr.FindNodeStr(nameOfVar,VList::listStr._head)->_name; };
		//unordered map which contains all the lambdas
		std::unordered_map<type,std::function<bool(void)>> _checkFunctions;
		_checkFunctions[type_int] = _checkInt;
		_checkFunctions[type_char] = _checkChar;
		_checkFunctions[type_bool] = _checkBool;
		_checkFunctions[type_string] = _checkString;
		size_t _checkIfVarExists = 0;
		//for loop to check if variable exists
		for(auto _iterator = _checkFunctions.begin(); _iterator != _checkFunctions.end(); ++_iterator) {
			if(_iterator->second()) {
				_checkIfVarExists++;
				break;
			}
		}
		if(_checkIfVarExists == 0) {
			UndeclaredVariable _undeclaredVariable(nameOfVar);
			throw _undeclaredVariable;
			return type_int;
		}
		type _ultType = type_int;
		//otherwise, if the variable does exist
		//extracts the type of the variable
		for(auto _iterator = _checkFunctions.begin(); _iterator != _checkFunctions.end(); ++_iterator) {
			if(_iterator->second()) {
				_ultType = _iterator->first;
				break;
			}
		}
		result = _ultType;
		return result;
	}
	catch(UndeclaredVariable udv) { udv.ThrowExeption(); }
	return type_default;
}
//function to calculate the number of spaces in a string
//every piece of string separated by a ' ' will be considered a
//word
inline size_t CompNumberOfSpaces(const std::string &rsv) {
	size_t _index = 0;
	size_t _numOfSpaces = 0;
	while(rsv[_index] != '\0') {
		if(rsv[_index] == ' ')_numOfSpaces++;
		_index++;
	}
	return _numOfSpaces;
}
inline std::string GetKeyword(const std::string &line) {
	std::string _keyword = "";
	size_t _index = 0;
	while(line[_index] != ' ' && _index < line.length()) {
		_keyword += line[_index];
		++_index;
	}
	return _keyword;
}