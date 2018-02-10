#pragma once
#include <iostream>
#include "Vector.h"
#include "RSValue.h"
class CalcParser {
private:
	//constant arrayof operations is used to simplify
	//the process of checking the operation 
	//and figuring out which function to call
	const char OPERATIONS[4] ={ '+','-','*','/' };
	//typedef of a pointer to a function that returns
	//a string (the stringified result)
	typedef std::string(CalcParser::*func_t)(std::string);
	//array of pointer to the functions
	//add(),sub() etc..
	func_t _basicArithmetic[4];		//add, sub, mul, div
	//returns an array of two numbers, used to work out
	//the answer to an operation
	unsigned int * GenerateStrInt(std::string exp) {
		std::string _arrNumStr[2];
		unsigned int * _arrNum = new unsigned int[2];
		unsigned int _arrSize = 0;
		unsigned int _index = 0;
		while(exp[_index] != '\0') {
			if(exp[_index] == ' ') {
				//when there is a space the computer
				//needs to add 3 to the index because the space is before the
				//operation and to get to the number it has
				//to add 3 example: 0.' '1.'+'2.' '3.'2' 
				_index += 3;
				_arrSize++;
			}
			//if the character represents a number
			if((int)exp[_index] >= 48 && (int)exp[_index] < 58) _arrNumStr[_arrSize] += exp[_index];
			_index++;
		}
		//converts the characters to integers
		for(int _arrIndex = 0; _arrIndex < 2; _arrIndex++)
			_arrNum[_arrIndex] = CalculateStrTOInt(_arrNumStr[_arrIndex]);
		return _arrNum;
	}
	std::string Add(std::string exp) {
		//fetches the array of integers from the function
		//GenerateStrInt(std::string);
		unsigned int * _arrNum = GenerateStrInt(exp);
		//the addition takes place here
		unsigned int _resultInt = _arrNum[0] + _arrNum[1];
		delete _arrNum;
		return ConvertIntToString(_resultInt);
	}
	std::string Sub(std::string exp) {
		unsigned int * _arrNum = GenerateStrInt(exp);
		//the subtraction takes place here
		unsigned int _resultInt = _arrNum[0] - _arrNum[1];
		delete _arrNum;
		return ConvertIntToString(_resultInt);
	}
	std::string Mul(std::string exp) {
		unsigned int * _arrNum = GenerateStrInt(exp);
		//the multiplication takes place here
		unsigned int _resultInt = _arrNum[0] * _arrNum[1];
		delete _arrNum;
		return ConvertIntToString(_resultInt);
	}
	std::string Div(std::string exp) {
		unsigned int * _arrNum = GenerateStrInt(exp);
		//the division takes place here
		unsigned int _resultInt = _arrNum[0] / _arrNum[1];
		delete _arrNum;
		return ConvertIntToString(_resultInt);
	}
	//function returns the new string, replacing the operation that had to be calculated
	//with the result of the operation
	//example: 2 * 3 + 5 -> 6 + 5
	std::string RenewExp(Vector<std::string> vecWords,unsigned int indexOfOp,std::string result) {
		std::string _newCurrExp = "";
		std::string _temp = "";
		for(unsigned int _indexVec = 0; _indexVec < vecWords._size; _indexVec++) {
			//checks for an string represented integer
			if((int)vecWords[_indexVec][0] >= 48 && (int)vecWords[_indexVec][0] < 58) _temp += vecWords[_indexVec];
			//when it reaches the operation character
			if(_indexVec == indexOfOp) {
				_temp = result;
				_indexVec++;
			}
			//if the index reached an operation
			if((_indexVec % 2 == 1 ||_indexVec == vecWords._size - 1)&& _indexVec != indexOfOp)
			{
				//continues to build the new string
				if(_indexVec != vecWords._size - 1) {
					_newCurrExp += _temp + vecWords[_indexVec] + ' ';
					_temp = "";
				}
				else _newCurrExp += _temp;
				continue;
			}
			if(_indexVec != vecWords._size - 1) _temp += ' ';
		}
		return _newCurrExp;
	}
	//function checks if there is a variable in the expression
	//if there is, the function replaces it with its actual
	//value - (recursive function)
	std::string CheckForVar(std::string exp) {
		size_t _index = 0;
		size_t _posOfVarSt = 0;
		size_t _posOfVarEnd = 0;
		std::string _befVar = "";
		std::string _afVar = "";
		bool _atVar = false;
		std::string _temp = "";
		while(_expression[_index] != '\0') {
			//creates a character _t because it is shorter to write
			//than _expression[_index]
			unsigned char _t = _expression[_index];
			if(_t != '('&&_t != ')') {
				//if it isn't any of the characters that are pre-assigned
				//to mean something
				if(((int)_t < 48 || (int)_t > 57) && (_t!= '+'&&_t != '-'&&_t != '*'&&_t != '/'&&_t != ' ')) {
					//adds to the temporary string (that will eventually be the variable)
					_temp += _t;
					if(!_atVar) _posOfVarSt = _index;
					_atVar = true;
				}
			}
			if(_atVar && (_t == ' '||_t == '('||_t ==')')) {
				_posOfVarEnd = _index;
				//takes what is before and after the variable
				//and builds the new expression to replace the 
				//variable to the value
				_befVar = ParseStrBefore(_posOfVarSt,_expression);
				_afVar = ParseStrAfter(_posOfVarEnd,_expression,true);
				_expression = _befVar + ConvertIntToString(VList::listInt.FindNodeStr(_temp,VList::listInt._head)->_value) + _afVar;
				//calls the function again
				return CheckForVar(_expression);
			}
			_index++;
		}
		//if there aren't anymore variables, it returns the expression
		return _expression;
	}
protected:
	//returns everything before a certain point in a string
	inline std::string ParseStrBefore(unsigned int posOfEnd, std::string exp) {
		std::string _result = "";
		unsigned int _index = 0;
		while(_index < posOfEnd) {
			_result += exp[_index];
			_index++;
		}
		return _result;
	}
	//returns everything after a certain point in a string
	inline std::string ParseStrAfter(unsigned int posOfStart, std::string exp,bool var = false) {
		std::string _result = "";
		unsigned int _index = posOfStart;
		if(exp[_index] == '\0') return _result;
		else if(exp[_index + 1] == '\0') {
			if(var) return _result + exp[_index];
			else return _result;
		}
		else if(exp[_index] != '\0') {
			_index = posOfStart;
			while(exp[_index] != '\0') {
				_result += exp[_index];
				_index++;
			}
		}
		return _result;
	}
	//calculates the number of words in a string
	inline unsigned int CalculateWords(std::string exp) {
		unsigned int _result = 1;
		unsigned int _index = 0;
		while(exp[_index] != '\0') {
			if(exp[_index] == ' ') _result++;
			_index++;
		}
		return _result;
	}
	std::string Reduce(std::string currExp,std::string oriStrBeforeP,std::string oriStrAfterP,unsigned int numOfBrackets = 0) {
		//checks if the number of spaces in the expression is > 1
		//because if it is, that means that the expression has just one value
		if(CalculateWords(currExp) > 1) {
			int _numOpenBracket = 0;
			int _numClosedBracket = 0;
			int _positionOfOpenBracket = 0;
			unsigned int _index = 0;
			std::string _temp = "";
			while(currExp[_index] != '\0') {
				//if the while loop meets a '('
				//that means that it must focus on it.
				//therefore the function will treat
				//the stuff in the bracket as the actual expression
				//until there is only one value left
				if(currExp[_index] == '(') {
					//if there has only been 1 '('
					//it will omit the '('
					//otherwise it keeps it
					if(_numOpenBracket == 0) {
						_numOpenBracket++;
						_positionOfOpenBracket = _index;
						_index++;
						_temp += currExp[_index];
					}
					else {
						_numOpenBracket++;
						_temp += currExp[_index];
					}
				}
				//if there is a closing bracket
				//it makes sure that it is the last one
				//of a nested bracket system like (3 + 2 * (4 - 1))
				else if(currExp[_index] == ')') {
					_numClosedBracket++;
					if(_numOpenBracket == _numClosedBracket) {
						if(_numOpenBracket > 1) {
							//it takes what is before the first bracket, including the '(' and ')'
							oriStrBeforeP += ParseStrBefore(_positionOfOpenBracket + 1,currExp);
							oriStrAfterP += ParseStrAfter(_index,currExp);
						}
						else {
							//it takes what is before the first bracket omitting the '(' and ')'
							oriStrBeforeP += ParseStrBefore(_positionOfOpenBracket,currExp);
							oriStrAfterP += ParseStrAfter(_index + 1,currExp);
						}
						//calls the function where the current expression is what is inside the brackets
						return Reduce(_temp,oriStrBeforeP,oriStrAfterP,_numOpenBracket);
					}
					else _temp += currExp[_index];
				}
				//only adds to the string if it's inside a bracket
				else if(_numOpenBracket > 0) _temp += currExp[_index];
				_index++;
			}
			//vector stores each word. -> a word is 
			//separated by a ' '
			Vector<std::string> _vecWords;
			std::string _tempWord = "";
			_index = 0;
			//the while loop simply
			//stores the words into the vector
			while(currExp[_index] != '\0') {
				if(currExp[_index] != ' ') {
					_tempWord += currExp[_index];
				}

				if(currExp[_index] == ' '||currExp[_index + 1] == '\0'){
					_vecWords.PushBack(_tempWord);
					_tempWord = "";
				}
				_index++;
			}
			//here it will calculate the result
			std::string _result = "";
			unsigned int _indexOfOp = 0;
			//it checks the operation is a multiplication or division
			for(unsigned int _indexVec = 0; _indexVec < _vecWords._size; _indexVec++) {
				for(unsigned int _op = 0; _op < 4; _op++) {
					if(_vecWords[_indexVec][0] == OPERATIONS[_op] && (OPERATIONS[_op] == '*' || OPERATIONS[_op] == '/')) {
						//it will call the function depending on the char
						_result = (*this.*_basicArithmetic[_op])(_vecWords[_indexVec - 1] + ' ' + _vecWords[_indexVec] + ' ' + _vecWords[_indexVec + 1]);
						_indexOfOp = _indexVec;
						goto MUL_DIV;
					}
				}
			}
			//if it is a multiplication / division
		MUL_DIV:if(_result != "") {
				//it creates an entirely new string
				//replacing the operation that it was calculating to the
				//result
				std::string _newCurrExp = RenewExp(_vecWords,_indexOfOp,_result);
				if(_newCurrExp == "") return Reduce(_result,oriStrBeforeP,oriStrAfterP,numOfBrackets);
				//it will then call the function again
				else return Reduce(_newCurrExp,oriStrBeforeP,oriStrAfterP,numOfBrackets);
			}
			//if there aren't any multiplications / divisions
			_result = "";
			_indexOfOp = 0;
			//it will check for the additions / subtractions
			for(unsigned int _indexVec = 0; _indexVec < _vecWords._size; _indexVec++) {
				for(int _op = 0; _op < 4; _op++) {
					if(_vecWords[_indexVec][0] == OPERATIONS[_op] && (OPERATIONS[_op] == '+' || OPERATIONS[_op] == '-')) {
						_result = (*this.*_basicArithmetic[_op])(_vecWords[_indexVec - 1] + ' ' + _vecWords[_indexVec] + ' ' + _vecWords[_indexVec + 1]);
						_indexOfOp = _indexVec;
						goto ADD_SUB;
					}
				}
			}
			ADD_SUB:std::string _newCurrExp = "";
			if(_vecWords._size == 3) _newCurrExp = _result;
			else std::string _newCurrExp = RenewExp(_vecWords,_indexOfOp,_result);
			//calls the function again
			return Reduce(_newCurrExp,oriStrBeforeP,oriStrAfterP,numOfBrackets);
		}
		else {
			//if there is only one word and the number of 
			//brackets is 0, then the function if finished
			if(numOfBrackets == 0) return currExp;
			else {
				//otherwise, it will return what was before the point of the operation + 
				//the currExp + what was after the point of the operation
				//example: bfre("2 + 3 * ") + currExp("3") + aftr(" + 1")
				numOfBrackets--;
				oriStrBeforeP = ParseStrBefore(oriStrBeforeP.length(),oriStrBeforeP);
				oriStrAfterP = ParseStrAfter(0/*doesn't matter*/,oriStrAfterP);
				if(oriStrAfterP == "")	currExp = oriStrBeforeP  + currExp + oriStrAfterP;
				else currExp = oriStrBeforeP + currExp + oriStrAfterP + ' ';
				//calls the function again
				return Reduce(currExp,"","",numOfBrackets);
			}
		}
	}
public:
	std::string _expression;
	CalcParser() {
		_basicArithmetic[0] = &CalcParser::Add;
		_basicArithmetic[1] = &CalcParser::Sub;
		_basicArithmetic[2] = &CalcParser::Mul;
		_basicArithmetic[3] = &CalcParser::Div;
	}
	~CalcParser() {}
	unsigned int Calculate() {
		//check for variables
		_expression = CheckForVar(_expression);
		unsigned int _answer = CalculateStrTOInt(Reduce(_expression,"",""));
		return _answer;
	}
};

