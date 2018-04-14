#pragma once
#include <iostream>
#include "Misc.h"

//if there is a block
//or a scop
//compiler makes sure to delete it
class ScopedVariable {
private:
	//type of the variable given by the user
	type _typeOfVar = type_default;

	//name of the variable given by the user
	std::string _nameOfVar = "";

	//type of the variable given by the user - in the form of a str
	std::string _typeOfVarStr = "";
	
	//function to work out the name of the variable
	//and the type of the variable 
	//the type will be stored in _typeOfVarStr
	void GetNameOfVarAndTypeStr(void) {
		size_t _index = 4;
		size_t _numOfUnitsCompleted = 0;
		while(_setLineString[_index] != '=') {
			if(_setLineString[_index] != ' ') {
				if((bool)_numOfUnitsCompleted) _nameOfVar += _setLineString[_index];
				if(!(bool)_numOfUnitsCompleted) _typeOfVarStr += _setLineString[_index];
			}
			else _numOfUnitsCompleted++;
			++_index;
		}
	}
	
	//will convert the _typeOfVarStr to _typeOfVar
	void ConvertTypeStrToType(type &typeToFind) {
		auto _typeIntLambda = [&](void)->void {typeToFind = type_int; };
		auto _typeCharLambda = [&](void)->void {typeToFind = type_char; };
		auto _typeBoolLambda = [&](void)->void {typeToFind = type_bool; };
		auto _typeStringLambda = [&](void)->void {typeToFind = type_string; };

		std::unordered_map<std::string,std::function<void(void)>> _mapOfTypeLambdas;
		_mapOfTypeLambdas["int"] = _typeIntLambda;
		_mapOfTypeLambdas["char"] = _typeCharLambda;
		_mapOfTypeLambdas["bool"] = _typeBoolLambda;
		_mapOfTypeLambdas["string"] = _typeStringLambda;

		for(auto _iterator = _mapOfTypeLambdas.begin(); _iterator != _mapOfTypeLambdas.end(); ++_iterator) {
			if(_iterator->first == _typeOfVarStr) {
				_iterator->second();
				break;
			}
		}
	}
public:
	std::string _setLineString = "";
	explicit ScopedVariable(void) = default;
	explicit ScopedVariable(const std::string &setLine) 
		: _setLineString(setLine) 
	{
	}
	~ScopedVariable(void) 
	{
	};
	//function to delete the variable from the linked list
	void Delete(void) {
		GetNameOfVarAndTypeStr();
		ConvertTypeStrToType(_typeOfVar);
		auto _intLambda = [&](void)->void {VList::listInt.DeleteNode(_nameOfVar,VList::listInt._head); };
		auto _charLambda = [&](void)->void {VList::listChar.DeleteNode(_nameOfVar,VList::listChar._head); };
		auto _boolLambda = [&](void)->void {VList::listBool.DeleteNode(_nameOfVar,VList::listBool._head); };
		auto _stringLambda = [&](void)->void {VList::listStr.DeleteNode(_nameOfVar,VList::listStr._head); };

		std::unordered_map<type,std::function<void(void)>> _possibleFunctions;
		_possibleFunctions[type_int] = _intLambda;
		_possibleFunctions[type_char] = _charLambda;
		_possibleFunctions[type_bool] = _boolLambda;
		_possibleFunctions[type_string] = _stringLambda;
		for(auto _iterator = _possibleFunctions.begin(); _iterator != _possibleFunctions.end(); ++_iterator) {
			if(_iterator->first == _typeOfVar) {
				_iterator->second();
				return;
			}
		}
	}
};