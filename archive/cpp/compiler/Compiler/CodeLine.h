#pragma once
#include "LinkedList.h"
#include "Variable.h"
#include "VarLists.h"
#include "RSValue.h"

//line of code
namespace CLine {
	const std::string STR_VAR[4] ={
		"int", "char", "bool", "string"
	};
	class CodeLine
	{
	protected:
		std::string _lineOfCode;
	public:
		CodeLine() {}
		~CodeLine() {}
		virtual void TranslateToCPP() = 0;
	};
	//anything linked to variables
	//like creating them and assigning them to a value
	class VarLines : public CodeLine {
	public:
		VarLines(){}
		~VarLines(){}
	};

	class SCLInitialize : public VarLines {
	private:
		//typedef a pointer to a function
		typedef void (SCLInitialize::*func_type)();
		//array of function pointers to make the process
		//of checking for a type less tedious,
		//i.e. having a ton of nested if statements
		func_type _checkType[4];
		//function for creating a variable
		void CreateVar() {
			_rsValue = new RSVVar(_rsString,_type);
			_rsValue->Translate(_name);
			return;
		}
		//function for creating an integer
		void FuncInt() {
			//checks if it is an operation
			if(GetNumSpacesRSV() > 0) {
				_rsValue = new RSVOperation(_rsString);
				_rsValue->Translate(_name);
				return;
			}
			//if not, checks for whether it is a variable
			else if(CheckIfRSVEquType()) CreateVar();	
			//if not, creates an int
			else {
				if((int)_rsString[0] >= 48 && (int)_rsString[0] <= 58) {
					_rsValue = new RSVConst(_rsString);
					_rsValue->Translate(_name);
					return;
				}
				else return;
			}
		}
		//function to create a character
		void FuncChar() {
			if(CheckIfRSVEquType() == false) {
				_rsValue = new RSVConst(_rsString);
				_rsValue->Translate(_name);
				return;
			}
			else CreateVar();
		}
		//function to create a boolean
		void FuncBool() {
			if(CheckIfRSVEquType() == false) {
				_rsValue = new RSVConst(_rsString);
				_rsValue->Translate(_name);
				return;
			}
			else CreateVar();
		}
		//function to create a string
		void FuncString() {
			if(CheckIfRSVEquType() == false) {
				_rsValue = new RSVString(_rsString);
				_rsValue->Translate(_name);
				return;
			}
			else CreateVar();
		}
		//creates a pointer to a right-side value
		RSValue * _rsValue;
		//string stores the type of the variable
		std::string _type;
		//string stores the right-side value (as a string)
		std::string _rsString;
		//string stores the name of the variable
		std::string _name;
		//if function returns false it means there is no variable
		bool CheckIfRSVEquType() {
			bool _couldBeVar[] = {true, false, false, true};  //bool, char, string, int
			bool _result = true;
			if(_rsString == "true"||_rsString == "false") _couldBeVar[0] = false;
			if(_rsString[0] != '\'') _couldBeVar[1] = true;
			if(_rsString[0] != '\"') _couldBeVar[2] = true;
			if((int)_rsString[0] >= 48 && (int)_rsString[0] <= 57) _couldBeVar[3] = false;
			for(int _indexCBV = 0; _indexCBV < 4; _indexCBV++) 
				_result = _result & _couldBeVar[_indexCBV];

			return _result;
		}
		//returns the name of the variable
		//being initialized
		std::string GetName() {
			size_t _index = 4 + _type.length() + 1;
			while(_lineOfCode[_index] != ' ') {
				_name += _lineOfCode[_index];
				_index++;
			}
			return _name;
		}
		//gets the type of the variable
		unsigned int GetType() {
			int _index = 4;
			while(_lineOfCode[_index] != ' ') {
				_type += _lineOfCode[_index];
				_index++;
			}
			return _index;
		}
		//creates a string storing what is after the '='
		//(right-side value)
		std::string CreateRSString(unsigned int posValue) {
			while(_lineOfCode[posValue] != ';') {
				_rsString += _lineOfCode[posValue];
				posValue++;
			}
			return _rsString;
		}
		//calculates how many spaces there are
		//in the rsv
		unsigned int GetNumSpacesRSV() {
			int _index2 = 0;
			int _numOfSpaces = 0;
			while(_rsString[_index2] != '\0') {
				if(_rsString[_index2] == ' ') _numOfSpaces++;
				_index2++;
			}
			return _numOfSpaces;
		}
		//instantiates a derived object of RSValue
		void Append() {
			unsigned int _index = GetType();
			GetName();
			unsigned int _positionOfValue = _index + _name.length() + 4;
			CreateRSString(_positionOfValue);
			for(size_t _index = 0; _index < 4; _index++) {
				if(_type == STR_VAR[_index]) (*this.*_checkType[_index])();
			}
		}
	public:
		SCLInitialize(std::string inputLine) {
			_lineOfCode = inputLine;
			//assigns each function of the array
			//to the corresponding function
			_checkType[0] = &SCLInitialize::FuncInt;
			_checkType[1] = &SCLInitialize::FuncChar;
			_checkType[2] = &SCLInitialize::FuncBool;
			_checkType[3] = &SCLInitialize::FuncString;
		}
		~SCLInitialize() {}
		virtual void TranslateToCPP() {
			Append();
		}
	};
	//technically it is assigning but
	//for this language, it will be modify or "mod"
	class SCLModify : public VarLines {
	private:
		std::string _rsString = "";
		typedef void (SCLModify::func_type_mod)() const;
		const std::string STR_TYPE[4] = {"int","char","bool","string"};
		std::string _nameVar;
		void FuncInt() const {}
		void FuncChar() const {}
		void FuncBool() const {}
		void FuncStr() const {}
		void CheckType() {
			if(VList::listInt.FindNodeStr(_nameVar,VList::listInt._head)->_name == _nameVar) _type = "int";
			else if(VList::listChar.FindNodeStr(_nameVar,VList::listChar._head)->_name == _nameVar) _type = "char";
			else if(VList::listBool.FindNodeStr(_nameVar,VList::listBool._head)->_name == _nameVar) _type = "bool";
			else if(VList::listStr.FindNodeStr(_nameVar,VList::listStr._head)->_name == _nameVar) _type = "string";
			else return;
		}
		std::string GetName() {
			size_t _index = 4;
			while(_lineOfCode[_index] != ' ') {
				_nameVar += _lineOfCode[_index];
				_index++;
			}
			return _nameVar;
		}
		void GetRsString() {
			size_t _index = 4 + _nameVar.length() + 5;
			while(_lineOfCode[_index] != ';') {
				_rsString += _lineOfCode[_index];
				_index++;
			}
		}
	public:
		std::string _type = "";
	};
}
