#pragma once
#include <unordered_map>
#include <functional>
#include <fstream>

#include "Misc.h"
#include "LList.h"
#include "Error.h"
#include "VLists.h"
#include "Parser.h"
#include "RSValue.h"
#include "Condition.h"
#include "Encryptions.h"
#include "ScopedVariable.h"

namespace CLine {
	//base class for all the classes in "CodeLine.h"
	class LineOfCode {
	public:
		std::string _lineOfCode = "";

		LineOfCode(void) {};
		~LineOfCode(void) {};
		
		//pure virtual function to translate the line of code
		//into C++
		virtual void TranslateToCPP(void) = 0;
		virtual bool IsDependentOfBody(void) { return false; };
		virtual bool IsVariableCreator(void) { return false; };
		virtual Vector<std::string>* GetBodyString(void) { return nullptr; };
		virtual Vector<LineOfCode*>* GetBodyLine(void) { return nullptr; };
		virtual bool IsStatementTrue(void) { return false; };	//for if statements
		virtual Vector<LineOfCode*>* GetVectorOfBlocksForIf(void) { return nullptr; };	//for if statements
	};

	//class for "set" keyword
	//the "set" keyword acts as an 
	//initialization
	class SetLineOfCode : public LineOfCode {
	private:
		//typedef for function pointers
		//to make an array
		typedef void(SetLineOfCode::*func_ptr)(void);
		//functions for each possible type
		//appends the values to the corresponding
		//linked list defined in "VLists.h"
		func_ptr _arrayOfFunctions[4];
		//function to get essential things like the type,
		//name of the variable being created
		//and the value
		func_ptr _getPartsOfLine[3];
		const std::string _possibleTypes[4] ={"int","char","bool","string"};
		//function for integer
		void FunctionInt(void) {
			//checks if there is more than one word
			//if there is, it means that there is an operation
			if(CompNumberOfSpaces(_rsString) > 0) {
				RSVOperation _operation(_rsString);
				int _result = (int)_operation.GetResult();
				VList::listInt.AppendInitializedVariable(_result,_nameOfVariable);
				return;
			}
			//if there is a variable (as the value)
			//it creates a variable
			else if(CheckVar(_rsString)) 
				VList::listInt.AppendInitializedVariable(CreateVariable<int>(0),_nameOfVariable); 
			else {
				//if it's just a regular integer, creates
				//something called Constant RightSide Value
				RSVConst<int> _constantInt(_rsString,0);
				VList::listInt.AppendInitializedVariable(_constantInt.Translate(),_nameOfVariable);
			}
		}
		//function for the characters

		//***********    for the rest of the function for each type
		//***********    it just checks if it's a variable or constant
		void FunctionChar(void) {
			if(CheckVar(_rsString))
				VList::listChar.AppendInitializedVariable(CreateVariable<char>(1),_nameOfVariable);
			else {
				RSVConst<char> _constantChar(_rsString,1);
				VList::listChar.AppendInitializedVariable(_constantChar.Translate(),_nameOfVariable);
				return;
			}
		}
		void FunctionBool(void) {
			if(CheckVar(_rsString))
				VList::listBool.AppendInitializedVariable(CreateVariable<bool>(2),_nameOfVariable);
			else {
				RSVConst<bool> _constantBool(_rsString,2);
				VList::listBool.AppendInitializedVariable(_constantBool.Translate(),_nameOfVariable);
			}
		}
		void FunctionString(void) {
			if(CheckVar(_rsString)) {
				std::string _value = "";
				_value = VList::listStr.FindNodeStr(_rsString,
					VList::listStr._head)->_value;
				VList::listStr.AppendInitializedVariable(_value,_nameOfVariable);
			}
			else {
				RSVString _string(_rsString);
				VList::listStr.AppendInitializedVariable(_string.Translate(),_nameOfVariable);
			}
		}
	protected:
		std::string _nameOfVariable = "";
		//string of the right-side value
		std::string _rsString = "";
		std::string _type = "";
		//inline function just to create a string, comprised in 
		//another. function takes the ending character,
		//index of the first character, the string to "build"
		inline std::string BuildString(const char end,size_t index,std::string &strToBuild) const {
			strToBuild = "";
			while(_lineOfCode[index] != end) {
				strToBuild += _lineOfCode[index];
				index++;
			}
			return strToBuild;
		}
		//function to get what type the 
		//variable being created is
		inline void GetType(void) {
			size_t _indexOfLine = 4;
			BuildString(' ',_indexOfLine,_type);
		}
		//function to get what the name of
		//the variable
		inline void GetName(void) {
			size_t _indexOfLine = 5 + _type.length();
			BuildString(' ',_indexOfLine,_nameOfVariable);
		}
		//function to get what the right-side value is
		inline void GetRSString(void) {
			size_t _indexOfLine = 5 + _type.length() + _nameOfVariable.length() + 3;
			BuildString(';',_indexOfLine,_rsString);
		}
		//template class to create a variable
		//to create a variable, one needs
		//to specify the type
		template<class Type>inline Type CreateVariable(size_t pos) {
			RSVVariable<Type> _variable(_rsString,pos);
			return _variable.Translate();
		}
		
		//following 3 functions are to 
		//check for certain errors

		//checks for missing semi colons
		bool CheckForSemiColon(std::string &correct) {
			if(correct[correct.length() - 1] != ';') {
				correct += ';';
				return true;
			}
			else return false;
		}
		//checks if the equal sign is misplaced
		bool CheckForEqualSign(Vector<std::string> &vec,std::string comments[3]) {
			if(vec[3] != "=") {
				comments[1] = "expected a \" = \" (with spaces)";
				return true;
			}
			else return false;
		}
		//checks if the type specified is invalid
		bool CheckForValidType(Vector<std::string> &vec,std::string comments[3]) {
			if(vec[1] != "int"&&vec[1] != "char"&&vec[1] != "bool"&&vec[1] != "string") {
				comments[2] = "invalid type \"" + vec[1] + '\"';
				return true;
			}
			else return false;
		}
		//inline function to put the words of a string
		//inside a vector
		inline void SeparateStringToWords(Vector<std::string> &vectorToMod) {
			size_t _index = 0;
			std::string _temp = "";
			while(_lineOfCode[_index] != '\0') {
				if(_lineOfCode[_index] != ' ' && _lineOfCode[_index + 1] != '\0')
					_temp += _lineOfCode[_index];
				else {
					vectorToMod.PushBack(_temp);
					_temp = "";
				}
				_index++;
			}
		}
	public:
		explicit SetLineOfCode(void)=default;
		explicit SetLineOfCode(const std::string &lineOfCode) {
			_lineOfCode = lineOfCode;
			//assigns each function to there index
			//in the arrays

			//essentials
			_getPartsOfLine[0] = &SetLineOfCode::GetType;
			_getPartsOfLine[1] = &SetLineOfCode::GetName;
			_getPartsOfLine[2] = &SetLineOfCode::GetRSString;

			//functions for each type
			_arrayOfFunctions[0] = &SetLineOfCode::FunctionInt;
			_arrayOfFunctions[1] = &SetLineOfCode::FunctionChar;
			_arrayOfFunctions[2] = &SetLineOfCode::FunctionBool;
			_arrayOfFunctions[3] = &SetLineOfCode::FunctionString;
		};
		~SetLineOfCode(void) {};
		//pure virtual to translate to C++
		bool IsVariableCreator(void) override { return true; };
		void TranslateToCPP(void) override {
			try {
				//_comments[0] -> comment of the missing semi colon
				//_comments[1] -> comment of the misplaced '='
				//_comments[2] -> comment of the invalid type
				std::string _comments[3];
				//for the missing semi colon, the program
				//will show the incorrect line, versus the new one
				std::string _newString = _lineOfCode;
				Vector<std::string> _vectorOfWords;
				SeparateStringToWords(_vectorOfWords);
				//checks for each error
				if(CheckForSemiColon(_newString)) {
					SyntaxError _missingSemiColon(_lineOfCode,_newString);
					throw _missingSemiColon;
					return;
				}
				if(CheckForEqualSign(_vectorOfWords,_comments)) {
					SyntaxError _errorWithEqualSign(_lineOfCode,_newString,_comments[1]);
					throw _errorWithEqualSign;
					return;
				}
				if(CheckForValidType(_vectorOfWords,_comments)) {
					SyntaxError _errorInvalidType(_lineOfCode,_newString,_comments[2]);
					throw _errorInvalidType;
					return;
				}
				//if there aren't any errors call all the functions
				for(size_t _indexGetParts = 0; _indexGetParts < 3; _indexGetParts++)
					(*this.*_getPartsOfLine[_indexGetParts])();
				for(size_t _index = 0; _index < 4; _index++)
					if(_possibleTypes[_index] == _type) 
						(*this.*_arrayOfFunctions[_index])();
			}
			catch(SyntaxError synError) { synError.ThrowException(); };
		}
	};

	//class for modification

	class ModLineOfCode : public LineOfCode {		//syntax: mod (name) -> (value);
	private:
		//all the different possibilities concerning the type
		type _possibilities[4] = {type_int,type_char,type_bool,type_string};
		//string of the right side value
		std::string _rsString = "";
		//name of the variable being modified
		std::string _name = "";
		type _type;
		typedef void(ModLineOfCode::*func_ptr)(void);
		//function for each type
		func_ptr _arrayOfFunctions[4];
	protected:
		//all functions for the right side values

		//function int:
		//checks for the spaces if it is an operation
		//checks for whether it is a variable
		//otherwise it is a constant
		void FunctionInt(void) {
			if(CompNumberOfSpaces(_rsString) > 0) {
				RSVOperation _operation(_rsString);
				int _result = (int)_operation.GetResult();
				VList::listInt.FindNodeStr(_name,
					VList::listInt._head)->_value = _operation.GetResult();
			}
			else if(CheckVar(_rsString)) VList::listInt.FindNodeStr(_name,
				VList::listInt._head)->_value = CreateVariable<int>(0);
			else {
				RSVConst<int> _constantInt(_rsString,0);
				VList::listInt.FindNodeStr(_name,
					VList::listInt._head)->_value = _constantInt.Translate();
			}
		}
		void FunctionChar(void) {
			if(CheckVar(_rsString)) VList::listChar.FindNodeStr(_name,
				VList::listChar._head)->_value = CreateVariable<char>(1);
			else {
				RSVConst<char> _constantChar(_rsString,1);
				VList::listChar.FindNodeStr(_name,
					VList::listChar._head)->_value = _constantChar.Translate();
			}
		}
		//just checks for a variable
		//otherwise it is just a constant
		void FunctionBool(void) {
			if(CheckVar(_rsString)) VList::listBool.FindNodeStr(_name,
				VList::listBool._head)->_value = CreateVariable<bool>(2);
			else {
				RSVConst<bool> _constantBool(_rsString,2);
				VList::listBool.FindNodeStr(_name,
					VList::listBool._head)->_value = _constantBool.Translate();
			}
		}
		void FunctionString(void) {
			if(CheckVar(_rsString)) {
				std::string _value = "";
				_value = VList::listStr.FindNodeStr(_rsString,VList::listStr._head)->_value;
				VList::listStr.FindNodeStr(_name,VList::listStr._head)->_value = _value;
			}
			else {
				RSVString _constantString(_rsString);
				VList::listStr.FindNodeStr(_name,
					VList::listStr._head)->_value = _constantString.Translate();
			}
		}
		//returns the name of the variable being modified
		std::string GetName(void) {
			size_t _index = 4;
			while(_lineOfCode[_index] != ' ') {
				_name += _lineOfCode[_index];
				_index++;
			}
			return _name;
		}
		//returns the right side value
		//in the form of a string
		std::string GetRSString(void) {
			size_t _index = 4 + _name.length() + 4;
			while(_lineOfCode[_index] != ';') {
				_rsString += _lineOfCode[_index];
				_index++;
			}
			return _rsString;
		}
		//function creates a variable
		template<class Type>inline Type CreateVariable(size_t pos) const {
			RSVVariable<Type> _variable(_rsString,pos);
			return _variable.Translate();
		}
		//function separates a string into "words"
		//"words are separated by spaces"
		void SeparateStringToWords(Vector<std::string> &vectorToMod){
			size_t _index = 0;
			std::string _temp = "";
			while(_lineOfCode[_index] != '\0') {
				if(_lineOfCode[_index] != ' ' && _lineOfCode[_index + 1] != '\0') 
					_temp += _lineOfCode[_index];
				else {
					vectorToMod.PushBack(_temp);
					_temp = "";
				}
				_index++;
			}
		}
		//function just checks if the user
		//remembered to put the arrow
		bool CheckForArrowSyntaxError(Vector<std::string> &vecWords, std::string comments[2]) {
			if(vecWords[2] != "->") {
				comments[1] = "expected a \" -> \" (with spaces)";
				return true;
			}
			else return false;
		}
		//checks if the user forgot the semi colon
		bool CheckForMissingSemiColon(std::string &correct, std::string comments[2]) {
			if(_lineOfCode[_lineOfCode.length() - 1] != ';') {
				comments[0] = "";
				correct += ';';
				return true;
			}
			else return false;
		};
	public:
		explicit ModLineOfCode(void)=default;
		explicit ModLineOfCode(const std::string &lineOfCode) { 
			_lineOfCode = lineOfCode; 
			GetName();
			GetRSString();
			//GetType(_name,_type);
		};

		void TranslateToCPP(void) override {
			try {
				GetType(_name,_type);
				Vector<std::string> _vectorOfWords;
				SeparateStringToWords(_vectorOfWords);
				std::string _correct = _lineOfCode;
				std::string _comments[2];
				//throws exception if the semi colon is missing
				if(CheckForMissingSemiColon(_correct,_comments)) {
					SyntaxError _missingSemiColon(_lineOfCode,_correct);
					throw _missingSemiColon;
					return;
				}
				//throws exception if the arrow is misplaced
				if(CheckForArrowSyntaxError(_vectorOfWords,_comments)) {
					SyntaxError _arrowIsIncorrect(_lineOfCode,_correct,_comments[1]);
					throw _arrowIsIncorrect;
				}
			
				_arrayOfFunctions[0] = &ModLineOfCode::FunctionInt;
				_arrayOfFunctions[1] = &ModLineOfCode::FunctionChar;
				_arrayOfFunctions[2] = &ModLineOfCode::FunctionBool;
				_arrayOfFunctions[3] = &ModLineOfCode::FunctionString;
				for(size_t _index = 0; _index < 4; _index++)
					if(_possibilities[_index] == _type) 
						(*this.*_arrayOfFunctions[_index])();
			}
			catch(SyntaxError synError) { synError.ThrowException(); };
		}
	};

	//class for print statements

	class PrintLineOfCode : public LineOfCode {
	private:
		type _possibleTypes[4] = {type_int,type_char,type_bool,type_string};
		type _actualType;
		std::string _rsString = "";
		//returns the right side value in a string form
		std::string GetRSString(void) {
			size_t _index = 6;
			while(_lineOfCode[_index] != ';') {
				_rsString += _lineOfCode[_index];
				_index++;
			}
			return _rsString;
		}
		//function where the printing happens
		void Print(void) {
			if(CheckVar(_rsString)) {
				GetType(_rsString,_actualType);
				//if it is printing a value of the variable obj
				auto _printInt = [=](void)->void {std::cout << VList::listInt.FindNodeStr(_rsString,
					VList::listInt._head)->_value;};
				auto _printChar = [=](void)->void {std::cout << VList::listChar.FindNodeStr(_rsString,
					VList::listChar._head)->_value; };
				auto _printBool = [=](void)->void {std::cout << VList::listBool.FindNodeStr(_rsString,
					VList::listBool._head)->_value; };
				auto _printString = [=](void)->void {
					//checking if the text is encrypted
					if(VList::listStr.FindNodeStr(_rsString,
						VList::listStr._head)->_isEncrypted == true) {
						for(size_t _index = 0; _index < VList::listStr.FindNodeStr(_rsString,
							VList::listStr._head)->_value.length(); _index++) {
							std::cout << std::hex << _rsString[_index] << ' ';
						}
					}
					else std::cout << VList::listStr.FindNodeStr(_rsString,
						VList::listStr._head)->_value;
				};
				std::unordered_map<type,std::function<void(void)>> _printType;
				_printType[type_int] = _printInt;
				_printType[type_char] = _printChar;
				_printType[type_bool] = _printBool;
				_printType[type_string] = _printString;
				for(auto _iterator = _printType.begin(); _iterator != _printType.end(); ++_iterator) {
					if(_iterator->first == _actualType) {
						_iterator->second();
						break;
					}
				}
			}
			else {
				//uses the RSVConst class to
				//get the value of the constant
				_actualType = GetTypeOfConst(_rsString,_actualType);
				auto _printConstInt = [=](void)->void {
					if(CompNumberOfSpaces(_rsString) > 0) {
						RSVOperation _operation(_rsString);
						std::cout << _operation.GetResult();
					}
					else {
						RSVConst<int> _constantInt(_rsString,0);
						std::cout << _constantInt.Translate();
					}
				};
				auto _printConstChar = [=](void)->void {
					RSVConst<char> _constantChar(_rsString,1);
					std::cout << _constantChar.Translate();
				};
				auto _printConstBool = [=](void)->void {
					RSVConst<bool> _constantBool(_rsString,2);
					std::cout << _constantBool.Translate();
				};
				auto _printConstString = [=](void)->void {
					RSVString _constantString(_rsString);
					std::cout << _constantString.Translate();
				};
				std::unordered_map<type,std::function<void(void)>> _printType;
				_printType[type_int] = _printConstInt;
				_printType[type_char] = _printConstChar;
				_printType[type_bool] = _printConstBool;
				_printType[type_string] = _printConstString;
				for(auto _iterator = _printType.begin(); _iterator != _printType.end(); ++_iterator) {
					if(_iterator->first == _actualType) {
						_iterator->second();
						break;
					}
				}
			}
		}
	public:
		explicit PrintLineOfCode(const std::string &lineOfCode) { 
			_lineOfCode = lineOfCode; 
			GetRSString();
		};
		~PrintLineOfCode(void) {};
		void TranslateToCPP(void) override {Print();}
	};

	//println : prints the string with a new line

	class PrintlnLineOfCode : public LineOfCode {
	private:
		type _possibleTypes[4] ={ type_int,type_char,type_bool,type_string };
		type _actualType;
		std::string _rsString = "";
		//returns the right side value in a string form
		std::string GetRSString(void) {
			size_t _index = 8;
			while(_lineOfCode[_index] != ';') {
				_rsString += _lineOfCode[_index];
				_index++;
			}
			return _rsString;
		}
		//function where the printing happens
		void Print(void) {
			if(CheckVar(_rsString)) {
				GetType(_rsString,_actualType);
				//if it is printing a value of the variable obj
				auto _printInt = [=](void)->void {std::cout << VList::listInt.FindNodeStr(_rsString,
					VList::listInt._head)->_value; };
				auto _printChar = [=](void)->void {std::cout << VList::listChar.FindNodeStr(_rsString,
					VList::listChar._head)->_value; };
				auto _printBool = [=](void)->void {std::cout << VList::listBool.FindNodeStr(_rsString,
					VList::listBool._head)->_value; };
				auto _printString = [=](void)->void {
					//checking if the text is encrypted
					if(VList::listStr.FindNodeStr(_rsString,
						VList::listStr._head)->_isEncrypted == true) {
						for(size_t _index = 0; _index < VList::listStr.FindNodeStr(_rsString,
							VList::listStr._head)->_value.length(); _index++) {
							std::cout << std::hex << _rsString[_index] << ' ';
						}
					}
					else std::cout << VList::listStr.FindNodeStr(_rsString,
						VList::listStr._head)->_value; 
				};
				std::unordered_map<type,std::function<void(void)>> _printType;
				_printType[type_int] = _printInt;
				_printType[type_char] = _printChar;
				_printType[type_bool] = _printBool;
				_printType[type_string] = _printString;
				for(auto _iterator = _printType.begin(); _iterator != _printType.end(); ++_iterator) {
					if(_iterator->first == _actualType) {
						_iterator->second();
						break;
					}
				}
			}
			else {
				//uses the RSVConst class to
				//get the value of the constant
				_actualType = GetTypeOfConst(_rsString,_actualType);
				auto _printConstInt = [=](void)->void {
					if(CompNumberOfSpaces(_rsString) > 0) {
						RSVOperation _operation(_rsString);
						std::cout << _operation.GetResult();
					}
					else {
						RSVConst<int> _constantInt(_rsString,0);
						std::cout << _constantInt.Translate();
					}
				};
				auto _printConstChar = [=](void)->void {
					RSVConst<char> _constantChar(_rsString,1);
					std::cout << _constantChar.Translate();
				};
				auto _printConstBool = [=](void)->void {
					RSVConst<bool> _constantBool(_rsString,2);
					std::cout << _constantBool.Translate();
				};
				auto _printConstString = [=](void)->void {
					RSVString _constantString(_rsString);
					std::cout << _constantString.Translate();
				};
				std::unordered_map<type,std::function<void(void)>> _printType;
				_printType[type_int] = _printConstInt;
				_printType[type_char] = _printConstChar;
				_printType[type_bool] = _printConstBool;
				_printType[type_string] = _printConstString;
				for(auto _iterator = _printType.begin(); _iterator != _printType.end(); ++_iterator) {
					if(_iterator->first == _actualType) {
						_iterator->second();
						break;
					}
				}
			}
		}
	public:
		explicit PrintlnLineOfCode(const std::string &lineOfCode) {
			_lineOfCode = lineOfCode;
			GetRSString();
		};
		~PrintlnLineOfCode(void) {};
		void TranslateToCPP(void) override { 
			Print(); 
			std::cout << std::endl;
		}
	};
	
	//class for inputing the values of the variables

	class InputLineOfCode : public LineOfCode {
	private:
		std::string _rsString = "";
		type _typeOfVariable;
		//function returns the right side value
		std::string GetRSString(void) {
			size_t _index = 6;
			while(_lineOfCode[_index] != ';') {
				_rsString += _lineOfCode[_index];
				_index++;
			}
			return _rsString;
		}
	protected:
		//function where the inputing happens
		void TakeInput(void) {
			GetType(_rsString,_typeOfVariable);
			std::unordered_map<type,std::function<void(void)>> _inputTypes;
			auto _inputInt = [=](void)->void {std::cin >> VList::listInt.FindNodeStr(_rsString,VList::listInt._head)->_value; };
			auto _inputChar = [=](void)->void {std::cin >> VList::listChar.FindNodeStr(_rsString,VList::listChar._head)->_value; };
			auto _inputBool = [=](void)->void {std::cin >> VList::listBool.FindNodeStr(_rsString,VList::listBool._head)->_value; };
			auto _inputString = [=](void)->void {
				std::getline(std::cin,VList::listStr.FindNodeStr(_rsString,VList::listStr._head)->_value);
				std::cin.ignore();
			};
			_inputTypes[type_int] = _inputInt;
			_inputTypes[type_char] = _inputChar;
			_inputTypes[type_bool] = _inputBool;
			_inputTypes[type_string] = _inputString;
			for(auto _iterator = _inputTypes.begin(); _iterator != _inputTypes.end(); ++_iterator) {
				if(_iterator->first == _typeOfVariable) {
					_iterator->second();
					break;
				}
			}
		}
	public:
		explicit InputLineOfCode(const std::string &lineOfCode) { 
			_lineOfCode = lineOfCode; 

			GetRSString();
		};
		~InputLineOfCode(void) {};
		void TranslateToCPP(void) override { TakeInput(); };
	};

	//************************************************		WORK IN PROGRESS
	//************************************************		WORK IN PROGRESS

	class IfStatement : public LineOfCode {
	private:
		Vector<LineOfCode*> _vectorOfIfAndElseLines;
	public:
		explicit IfStatement(void) = default;
		explicit IfStatement(const Vector<LineOfCode*> vecOfLines)
			: _vectorOfIfAndElseLines(vecOfLines)
		{
		}
		~IfStatement(void)
		{
		}
		void TranslateToCPP(void) override {
			bool _valueOfPreviousIf = false;
			size_t _index = 0;
			while(_index < _vectorOfIfAndElseLines._size) {
				if(_valueOfPreviousIf == false) {
					_vectorOfIfAndElseLines[_index]->TranslateToCPP();
					_valueOfPreviousIf = _vectorOfIfAndElseLines[_index]->IsStatementTrue();
				}
				else break;
				_index++;
			}
		}
		bool IsDependentOfBody(void) { return true; };
		bool IsVariableCreator(void) { return false; };
		Vector<LineOfCode*>* GetBodyLine(void) { return &_vectorOfIfAndElseLines; };
		Vector<LineOfCode*>* GetVectorOfBlocksForIf(void) override { return &_vectorOfIfAndElseLines; };	//for if statements
	};

	class IfLineOfCode : public LineOfCode {
	private:
		//gets the indexes of the else ifs and else
		Vector<size_t> _vectorOfIndexOfBlocks;
		bool _isConditionTrue = false;

		std::string _strCondition = "";
		std::string GetConditionString(const std::string &ifLine) {
			size_t _index = 3;
			std::string _newString = "";
			while(ifLine[_index] != '\0') {
				_newString += ifLine[_index];
				_index++;
			}
			return _newString;
		}
		/*void GetIndexesOfBlocks(void) {
			//to skip the first "begin" line
			size_t _index = 1;
			size_t _numOfBegins = 0;
			size_t _numOfEnds = 0;
			
			while(_index < _vectorOfStrings._size) {
				if(_numOfBegins == _numOfEnds) {
					if(GetKeyword(_vectorOfStrings[_index]) == "elif") {
						_vectorOfIndexOfBlocks.PushBack(_index);
						_vectorOfKeywordsOfBlocks.PushBack("elif");
					}
					else if(GetKeyword(_vectorOfStrings[_index]) == "else") {
						_vectorOfIndexOfBlocks.PushBack(_index);
						_vectorOfKeywordsOfBlocks.PushBack("else");
					}
				}
				if(_vectorOfStrings[_index] == "begin") _numOfBegins++;
				else if(_vectorOfStrings[_index] == "end" && _index != _vectorOfStrings._size - 1) _numOfEnds++;
				_index++;
			}
		}*/
	public:
		Condition _conditionObj;
		Vector<std::string> _vectorOfStrings;
		Vector<LineOfCode*> _vectorOfLines;
		explicit IfLineOfCode(void) = default;
		explicit IfLineOfCode(Vector<std::string> &vecOfStrings) {
			_strCondition = vecOfStrings[0];
			for(size_t _index = 1; _index < vecOfStrings._size; _index++) 
				_vectorOfStrings.PushBack(vecOfStrings[_index]);

			_conditionObj._condition = GetConditionString(_strCondition);
			_conditionObj.Init();
		};
		~IfLineOfCode(void) {};

		void TranslateToCPP(void) override {
			const std::string _conditionOfIf = _conditionObj._condition;
			_isConditionTrue = _conditionObj.Compare();
			if(_isConditionTrue) {
				Vector<ScopedVariable> _vectorOfScopedVariables;
				size_t _numOfScpVar = 0;
				for(size_t _index = 0; _index < _vectorOfLines._size; _index++) {
					if(_vectorOfLines[_index]->IsVariableCreator()) {
						ScopedVariable _scpVar(_vectorOfLines[_index]->_lineOfCode);
						_vectorOfScopedVariables.PushBack(_scpVar);
						++_numOfScpVar;
					}
					_vectorOfLines[_index]->TranslateToCPP();
				}
				for(size_t _indexOfScpVar = 0; _indexOfScpVar < _numOfScpVar; _indexOfScpVar++)
					_vectorOfScopedVariables[_indexOfScpVar].Delete();

				_conditionObj.Update(_conditionOfIf);
			}
			else _conditionObj.Update(_conditionOfIf);
		}
		bool IsDependentOfBody(void) override { return true; };
		bool IsStatementTrue(void) override { return _isConditionTrue; };
		Vector<std::string>* GetBodyString(void) override { return &_vectorOfStrings; };
		Vector<LineOfCode*>* GetBodyLine(void) override { return &_vectorOfLines; };
	};

	class ElifLineOfCode : public LineOfCode {
	private:
		Vector<std::string> _vectorOfStrings;
		Vector<LineOfCode*> _vectorOfLines; 
		std::string _lineOfCondition; 
		bool _valueOfCondition;
		Condition _conditionObj;
		std::string GetConditionString(const std::string &ifLine) {
			size_t _index = 5;
			std::string _newString = "";
			while(ifLine[_index] != '\0') {
				_newString += ifLine[_index];
				_index++;
			}
			return _newString;
		}
	public:
		explicit ElifLineOfCode(void) = default;
		explicit ElifLineOfCode(Vector<std::string> vecStr) {
			_lineOfCondition = vecStr[0];
			for(size_t _index = 1; _index < vecStr._size; _index++)
				_vectorOfStrings.PushBack(vecStr[_index]);
			_conditionObj._condition = GetConditionString(_lineOfCondition); 
			_conditionObj.Init();
		}
		~ElifLineOfCode(void) 
		{
		}
		void TranslateToCPP(void) override {
			const std::string _conditionOfIf = _conditionObj._condition;
			_valueOfCondition = _conditionObj.Compare();
			if(_valueOfCondition) {
				Vector<ScopedVariable> _vectorOfScopedVariables;
				size_t _numOfScpVar = 0;
				for(size_t _index = 0; _index < _vectorOfLines._size; _index++) {
					if(_vectorOfLines[_index]->IsVariableCreator()) {
						ScopedVariable _scpVar(_vectorOfLines[_index]->_lineOfCode);
						_vectorOfScopedVariables.PushBack(_scpVar);
						++_numOfScpVar;
					}
					_vectorOfLines[_index]->TranslateToCPP();
				}
				for(size_t _indexOfScpVar = 0; _indexOfScpVar < _numOfScpVar; _indexOfScpVar++)
					_vectorOfScopedVariables[_indexOfScpVar].Delete();
				_conditionObj.Update(_conditionOfIf);
			}
			else _conditionObj.Update(_conditionOfIf);
		}
		bool IsDependentOfBody(void) override { return true; };
		Vector<std::string>* GetBodyString(void) override { return &_vectorOfStrings; };
		Vector<LineOfCode*>* GetBodyLine(void) override { return &_vectorOfLines; };
		bool IsStatementTrue(void) override { return _valueOfCondition; };
	};

	class ElseLineOfCode : public LineOfCode {
	private:
		Vector<std::string> _vectorOfStrings;
		Vector<LineOfCode*> _vectorOfLines;
	public:
		explicit ElseLineOfCode(void) = default;
		explicit ElseLineOfCode(Vector<std::string> vecStr) {
			for(size_t _index = 1; _index < vecStr._size; _index++)
				_vectorOfStrings.PushBack(vecStr[_index]);
		}
		~ElseLineOfCode(void)
		{
		}
		void TranslateToCPP(void) override {
			Vector<ScopedVariable> _vectorOfScopedVariables;
			size_t _numOfScpVar = 0;
			for(size_t _index = 0; _index < _vectorOfLines._size; _index++) {
				if(_vectorOfLines[_index]->IsVariableCreator()) {
					ScopedVariable _scpVar(_vectorOfLines[_index]->_lineOfCode);
					_vectorOfScopedVariables.PushBack(_scpVar);
					++_numOfScpVar;
				}
				_vectorOfLines[_index]->TranslateToCPP();
			}
			for(size_t _indexOfScpVar = 0; _indexOfScpVar < _numOfScpVar; _indexOfScpVar++)
				_vectorOfScopedVariables[_indexOfScpVar].Delete();
		}
		bool IsDependentOfBody(void) override { return true; };
		Vector<std::string>* GetBodyString(void) override { return &_vectorOfStrings; };
		Vector<LineOfCode*>* GetBodyLine(void) override { return &_vectorOfLines; };
		bool IsStatementTrue(void) override { return false; };
	};

	//**********************************************		WORK IN PROGRESS
	//**********************************************		WORK IN PROGRESS



	//for loops - syntax: for [name of initialized variable] [operator of condition] [operator of increment] 

	class ForLineOfCode : public LineOfCode {
	private:
		Vector<std::string> _vectorOfStrings;
		Vector<LineOfCode*> _vectorOfLines;
		std::string _forLine = "";
		std::string _nameOfVarIncremented = "";
		char _operatorOfIncrement;
		Condition _conditionObj;
		void GetNameOfVarIncremented(const std::string &lineOfFor) {
			size_t _index = 5;
			while(lineOfFor[_index] != ']') {
				_nameOfVarIncremented += lineOfFor[_index];
				_index++;
			}
		}
		std::string GetConditionString(const std::string &lineOfFor) const {
			//index of the first character of the if statement
			size_t _index = 4;
			std::string _conditionString = "";
			//lineOfFor.length() - 2 brings the index to the last ']'
			while(_index < lineOfFor.length() - 1) {
				_conditionString += lineOfFor[_index];
				_index++;
			}
			return _conditionString;
		}
		void GetOperatorOfIncrement(const std::string &lineOfFor) {_operatorOfIncrement = lineOfFor[lineOfFor.length() - 1];}
		void Increment(char &operatorOfFor) {
			if(operatorOfFor == '+') VList::listInt.FindNodeStr(_nameOfVarIncremented,VList::listInt._head)->_value++;
			if(operatorOfFor == '-') VList::listInt.FindNodeStr(_nameOfVarIncremented,VList::listInt._head)->_value--;
			else return;			//THROW ERROR	
		}
	public:
		explicit ForLineOfCode(void) = default;
		explicit ForLineOfCode(Vector<std::string> &vecOfStrings) {
			_forLine = vecOfStrings[0];
			for(size_t _index = 1; _index < vecOfStrings._size; _index++)
				_vectorOfStrings.PushBack(vecOfStrings[_index]);
		};
		~ForLineOfCode(void) {};
		void TranslateToCPP(void) override {
			GetNameOfVarIncremented(_forLine);
			_conditionObj._condition = GetConditionString(_forLine);
			const std::string _conditionOfFor = _conditionObj._condition;
			GetOperatorOfIncrement(_forLine);
			Vector<ScopedVariable> _vectorOfScopedVariables;
			size_t _numOfScpVar = 0;
			size_t _indexOfForLoop = 0;
			_conditionObj.Init();
			while(_conditionObj.Compare()) {
				_numOfScpVar = 0;
				for(size_t _index = 0; _index < _vectorOfLines._size; _index++) {
					if(_vectorOfLines[_index]->IsVariableCreator()) {
						ScopedVariable _scpVar(_vectorOfLines[_index]->_lineOfCode);
						_vectorOfScopedVariables.PushBack(_scpVar);
						++_numOfScpVar;
					}
					std::string _debug = _vectorOfLines[_index]->_lineOfCode;
					_vectorOfLines[_index]->TranslateToCPP();
				}
				_indexOfForLoop++;
				Increment(_operatorOfIncrement);
				_conditionObj.Update(_conditionOfFor);
				for(size_t _indexOfScpVar = 0; _indexOfScpVar < _numOfScpVar; _indexOfScpVar++)
					_vectorOfScopedVariables[_indexOfScpVar].Delete();
			}
		}
		bool IsDependentOfBody(void) override { return true; };
		Vector<std::string>* GetBodyString(void) override { return &_vectorOfStrings; };
		Vector<LineOfCode*>* GetBodyLine(void) override { return &_vectorOfLines; };
	};

	//while loops - syntax: while [val1] operator [val2]
	
	class WhileLineOfCode : public LineOfCode {
	private:
		Vector<std::string> _vectorOfStrings;
		Vector<LineOfCode*> _vectorOfLines;
		std::string _whileLine = "";
		Condition _conditionObj;
		std::string GetConditionString(const std::string whileLine) {
			std::string _result;
			size_t _index = 6;
			while(whileLine[_index] != '\0') {
				_result += whileLine[_index];
				_index++;
			}
			return _result;
		}
	public:
		explicit WhileLineOfCode(void) = default;
		explicit WhileLineOfCode(Vector<std::string> vecStrings) {
			_whileLine = vecStrings[0];
			for(size_t _index = 1; _index < vecStrings._size; _index++)
				_vectorOfStrings.PushBack(vecStrings[_index]);
		}
		void TranslateToCPP(void) override {
			_conditionObj._condition = GetConditionString(_whileLine);
			const std::string _conditionOfWhile = _conditionObj._condition;
			Vector<ScopedVariable> _vectorOfScopedVariables;
			size_t _numOfScpVar = 0;
			_conditionObj.Init();
			while(_conditionObj.Compare()) {
				_numOfScpVar = 0;
				for(size_t _index = 0; _index < _vectorOfLines._size; _index++) {
					if(_vectorOfLines[_index]->IsVariableCreator()) {
						ScopedVariable _scpVar(_vectorOfLines[_index]->_lineOfCode);
						_vectorOfScopedVariables.PushBack(_scpVar);
						++_numOfScpVar;
					}
					std::string _debug = _vectorOfLines[_index]->_lineOfCode;
					_vectorOfLines[_index]->TranslateToCPP();
				}
				_conditionObj.Update(_conditionOfWhile);
				for(size_t _indexOfScpVar = 0; _indexOfScpVar < _numOfScpVar; _indexOfScpVar++)
					_vectorOfScopedVariables[_indexOfScpVar].Delete();
			}
		}
		bool IsDependentOfBody(void) override { return true; };
		Vector<std::string>* GetBodyString(void) override { return &_vectorOfStrings; };
		Vector<LineOfCode*>* GetBodyLine(void) override { return &_vectorOfLines; };
	};

	//to save variables

	class SaveLineOfCode : public LineOfCode {
	private:
		typedef void(SaveLineOfCode::*func)(void);
		func _arrayFunctionsForTypes[4];
		type _typeOfRSV;
		std::ofstream _fileToSave;
		std::string _directory = "";

		//rsString represents the value being saved
		std::string _rsString = "";

		void GetDirectory(const std::string &line) {
			size_t _index = 6;
			while(line[_index] != '\"') {
				_directory += line[_index];
				++_index;
			}
			_directory;
		}
		void GetRSString(const std::string &line) {
			size_t _index = 6 + _directory.length() + 2;
			while(line[_index] != ';') {
				_rsString += line[_index];
				++_index;
			}
		}
	protected:
		void FunctionInt(void) {
			if(CompNumberOfSpaces(_rsString) > 0) {
				RSVOperation _operation(_rsString);
				int _result = (int)_operation.GetResult();
				_fileToSave << _result;
				return;
			}
			else if(CheckVar(_rsString)) {
				RSVVariable<int> _intVar(_rsString,0);
				int _valueOfVar = _intVar.Translate();
				_fileToSave << _valueOfVar;
				return;
			}
			else {
				RSVConst<int> _constantInt(_rsString,0);
				signed int _valueOfConstant = _constantInt.Translate();
				_fileToSave << _valueOfConstant;
				return;
			}
		}
		void FunctionChar(void) {
			if(CheckVar(_rsString)) {
				RSVVariable<char> _charVar(_rsString,1);
				char _valueOfVar = _charVar.Translate();
				_fileToSave << '\'' << _valueOfVar << '\'';
				return;
			}
			else {
				RSVConst<char> _constantChar(_rsString,1);
				char _valueOfConstant = _constantChar.Translate();
				_fileToSave << '\'' << _valueOfConstant << '\'';
				return;
			}
		}
		void FunctionBool(void) {
			if(CheckVar(_rsString)) {
				RSVVariable<bool> _boolVar(_rsString,2);
				bool _valueOfVar = _boolVar.Translate();
				_fileToSave << _valueOfVar ? "true" : "false";
				return;
			}
			else {
				RSVConst<bool> _constantBool(_rsString,2);
				bool _valueOfConstant = _constantBool.Translate();
				_fileToSave << _valueOfConstant ? "true" : "false";
				return;
			}
		}
		void FunctionString(void) {
			if(CheckVar(_rsString)) {
				std::string _value = "";
				_value = VList::listStr.FindNodeStr(_rsString,
					VList::listStr._head)->_value;
				_fileToSave << '\"' << _value << '\"';
				return;
			}
			else {
				RSVString _constantString(_rsString);
				std::string _valueOfConstant = _constantString.Translate();
				_fileToSave << '\"' << _valueOfConstant << '\"';
				return;
			}
		}
	public:
		explicit SaveLineOfCode(void) = default;
		explicit SaveLineOfCode(const std::string &line) { 
			_lineOfCode = line; 

			_arrayFunctionsForTypes[0] = &SaveLineOfCode::FunctionInt;
			_arrayFunctionsForTypes[1] = &SaveLineOfCode::FunctionChar;
			_arrayFunctionsForTypes[2] = &SaveLineOfCode::FunctionBool;
			_arrayFunctionsForTypes[3] = &SaveLineOfCode::FunctionString;
		}; 
		~SaveLineOfCode(void) {};
		void TranslateToCPP(void) override {
			GetDirectory(_lineOfCode);
			GetRSString(_lineOfCode);
			_fileToSave.open(_directory);

			_typeOfRSV = type_default;

			GetTypeOfConst(_rsString,_typeOfRSV);
			if(_typeOfRSV == type_default) GetType(_rsString,_typeOfRSV);

			
			(*this.*_arrayFunctionsForTypes[_typeOfRSV])();
			_fileToSave.close();
		}
	};
	class ReadLineOfCode : public LineOfCode {
	private:
		typedef void(ReadLineOfCode::*func)(const std::string&);
		func _functionsForEachType[5];

		std::ifstream _fileToReadFrom;
		std::string _directory;
		std::string _varToReadTo;
		std::string _contents;

		type _typeOfContents = type_default;
		type _typeOfVariable = type_default;
		type _typeOfOperation = type_default;

		void GetDirectory(const std::string &line) {
			size_t _index = 6;
			while(line[_index] != '\"') {
				_directory += line[_index];
				_index++;
			}
		}
		void GetVarToReadToStr(const std::string &line) {
			size_t _index = 6 + _directory.length() + 2;
			while(line[_index] != ';') {
				_varToReadTo += line[_index];
				_index++;
			}
		}
		void GetContentsOfFile(void) { std::getline(_fileToReadFrom, _contents); }
	protected:
		void FunctionInt(const std::string &cont) {
			RSVConst<int> _constantInt(cont,0);
			VList::listInt.FindNodeStr(_varToReadTo,
				VList::listInt._head)->_value = _constantInt.Translate();
		}
		void FunctionChar(const std::string &cont) {
			RSVConst<char> _constantChar(cont,1);
			VList::listChar.FindNodeStr(_varToReadTo,
				VList::listChar._head)->_value = _constantChar.Translate();
		}
		void FunctionBool(const std::string &cont) {
			RSVConst<bool> _constantBool(cont,2);
			VList::listBool.FindNodeStr(_varToReadTo,
				VList::listBool._head)->_value = _constantBool.Translate();
		}
		void FunctionString(const std::string &cont) {
			RSVString _constantString(cont);
			VList::listStr.FindNodeStr(_varToReadTo,
				VList::listStr._head)->_value = _constantString.Translate();
		}
		void FunctionOtherwise(const std::string &cont) {
			IncorrectTypeConversion _errorOfType("check file");
			_errorOfType.ThrowException();
		}
	public:
		explicit ReadLineOfCode(void) = default;
		explicit ReadLineOfCode(const std::string &line) {
			_lineOfCode = line;
			_functionsForEachType[0] = &ReadLineOfCode::FunctionInt;
			_functionsForEachType[1] = &ReadLineOfCode::FunctionChar;
			_functionsForEachType[2] = &ReadLineOfCode::FunctionBool;
			_functionsForEachType[3] = &ReadLineOfCode::FunctionString;
			_functionsForEachType[4] = &ReadLineOfCode::FunctionOtherwise;
		}

		void TranslateToCPP(void) override {
			GetDirectory(_lineOfCode);
			_fileToReadFrom.open(_directory);

			GetVarToReadToStr(_lineOfCode);
			GetContentsOfFile();

			GetType(_varToReadTo,_typeOfVariable);
			GetTypeOfConst(_contents, _typeOfContents);

			if(_typeOfVariable == _typeOfContents) _typeOfOperation = _typeOfVariable;
			else _typeOfOperation = type_default;	//remains default

			(*this.*_functionsForEachType[_typeOfOperation])(_contents);
			_fileToReadFrom.close();
		}
	};

	//Encryption : XOR and Steganography
	
	class EncryptLineOfCode : public LineOfCode {
	private:
		Encryption* _encryption;
		std::string _encryptionStr = "";
		std::string _key = "";
		std::string _rsString = "";
		std::string _destination = "";
		
		std::string& GetEncryptionString(const std::string &line) const {
			std::string _tempStrOfEnc = "";
			size_t _index = 8;
			while(line[_index] != ' ') {
				_tempStrOfEnc += line[_index];
				_index++;
			}
			return _tempStrOfEnc;
		}
		Encryption* GetTypeOfEncryption(std::string &encStr) {
			std::unordered_map<std::string,std::function<Encryption*(void)>> _mapToFindEncType;
			auto _lambdaForXOR = [&](void)->Encryption* {
				return (new XOR_Encryption());
			};
			_mapToFindEncType["XOR"] = _lambdaForXOR;
			return _mapToFindEncType[encStr]();
		}
		std::string& GetStrToEncrypt(const std::string &line) const {
			std::string _tempStrToEncrypt = "";
			size_t _index = 8 + _encryptionStr.length() + 3;
			while(line[_index] != ' ') {
				_tempStrToEncrypt += line[_index];
				_index++;
			}
			return _tempStrToEncrypt;
		}
		std::string& GetKeyToEncryptWith(const std::string &line) const {
			std::string _tempStrOfKey = "";
			size_t _index = 8 + _encryptionStr.length() + 3 + _rsString.length() + 4;
			while(line[_index] != ')') {
				_tempStrOfKey += line[_index];
				_index++;
			}
			return _tempStrOfKey;
		}
		std::string& GetVarToStoreEncryption(const std::string &line) const {
			std::string _tempStrToStore = "";
			size_t _index = 8 + _encryptionStr.length() + 3 + _rsString.length() + 4 + _key.length() + 3;
			while(line[_index] != ';') {
				_tempStrToStore += line[_index];
				_index++;
			}
			return _tempStrToStore;
		}
	public:
		explicit EncryptLineOfCode(void) = default;
		explicit EncryptLineOfCode(std::string& line) { this->_lineOfCode = line; };
		void TranslateToCPP(void) override {
			GetEncryptionString(_lineOfCode);
			_encryption = GetTypeOfEncryption(_encryptionStr);
			_rsString =	GetStrToEncrypt(_lineOfCode);
			_key = GetKeyToEncryptWith(_lineOfCode);
			_destination = GetVarToStoreEncryption(_lineOfCode);
		}
	};
}