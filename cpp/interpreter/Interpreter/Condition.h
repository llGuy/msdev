#pragma once
#include "Misc.h"

class Condition {
private:
	enum operand {
		equ = 0,great = 1,less = 2,not = 3
	};
	bool _isConditionTrue;
	std::string _rsValue[2] ={ "","" };
	bool _isVariable[2] ={ false,false };
	type _typesOfRSV = type_default;
	size_t _index = 1;
	operand _operand;
	typedef void(Condition::*func_ptr)(void);
	func_ptr _arrayTypeFunctions[4];
	void GetValueOfFirstCondition(void) {
		while(_condition[_index] != ']') {
			_rsValue[0] += _condition[_index];
			_index++;
		}
		_index += 2;
	}
	void GetValueOfSecondCondition(void) {
		_index += 3;
		while(_condition[_index] != ']') {
			_rsValue[1] += _condition[_index];
			_index++;
		}
	}
	void GetOperand(void) {
		char _tempOperand = _condition[_index];
		std::unordered_map<operand,char> _operandMap;
		_operandMap[equ] = '=';
		_operandMap[great] = '>';
		_operandMap[less] = '<';
		_operandMap[not] = '!';
		for(auto _iterator = _operandMap.begin(); _iterator != _operandMap.end(); ++_iterator) {
			if(_iterator->second == _tempOperand) {
				_operand = _iterator->first;
				break;
			}
		}
	}
	void GetTypeOfCondition(void) {
		for(size_t _indexArray = 0; _indexArray < 2; _indexArray++) {
			type _tempType = GetTypeOfConst(_rsValue[_indexArray],_typesOfRSV);
			if(_tempType == type_default) {
				if(CompNumberOfSpaces(_rsValue[_indexArray]) == 0) {
					_isVariable[_indexArray] = true;
					GetType(_rsValue[_indexArray],_typesOfRSV);
				}
				else {
					_isVariable[_indexArray] = false;
					_typesOfRSV = type_int;
				}
			}
			else {
				_isVariable[_indexArray] = false;
				switch(_tempType) {
				case type_int:
					_typesOfRSV = type_int;
					return;
				case type_char:
					_typesOfRSV = type_char;
					return;
				case type_bool:
					_typesOfRSV = type_bool;
					return;
				case type_string:
					_typesOfRSV = type_string;
					return;
				}
			}
		}
	}
	template<class T> bool PerformOperand(T param1,T param2) {
		auto _equalLambda = [=](void)->bool {return param1 == param2; };
		auto _greaterLambda = [=](void)->bool {return param1 > param2; };
		auto _lesserLambda = [=](void)->bool {return param1 < param2; };
		auto _notLambda = [=](void)->bool {return param1 != param2; };
		std::unordered_map<operand,std::function<bool(void)>> _mapOperands;
		_mapOperands[equ] = _equalLambda;
		_mapOperands[great] = _greaterLambda;
		_mapOperands[less] = _lesserLambda;
		_mapOperands[not] = _notLambda;

		for(auto _iterator = _mapOperands.begin(); _iterator != _mapOperands.end(); ++_iterator)
			if(_iterator->first == _operand) {
				_isConditionTrue = _iterator->second();
				return _iterator->second();
			}		
		return false;
	}
	void FunctionInt(void) {
		int _arrayRSActualValues[2];
		for(size_t _indexRSV = 0; _indexRSV < 2; _indexRSV++) {
			if(CompNumberOfSpaces(_rsValue[_indexRSV]) > 0) {
				RSVOperation _operation(_rsValue[_indexRSV]);
				_arrayRSActualValues[_indexRSV] = _operation.GetResult();
			}
			else if(CheckVar(_rsValue[_indexRSV])) {
				RSVVariable<int> _variable(_rsValue[_indexRSV],0);
				_arrayRSActualValues[_indexRSV] = _variable.Translate();
			}
			else {
				RSVConst<int> _constant(_rsValue[_indexRSV],0);
				_arrayRSActualValues[_indexRSV] = _constant.Translate();
			}
		}
		//it is important to assign a value to 
		//_isConditionTrue so that the Compare() function 
		//can return
		PerformOperand<int>(_arrayRSActualValues[0],_arrayRSActualValues[1]);
	}
	void FunctionChar(void) {CreateVarAndConst<char>(1);}
	void FunctionBool(void) {CreateVarAndConst<bool>(2);}
	void FunctionString(void) {
		std::string _arrayRSActualValues[2];
		for(size_t _indexRSV = 0; _indexRSV < 2; _indexRSV++) {
			if(CheckVar(_rsValue[_indexRSV])) {
				_arrayRSActualValues[_indexRSV] = VList::listStr.FindNodeStr(_rsValue[_indexRSV],
					VList::listStr._head)->_value;
			}
			else {
				RSVString _constantString(_rsValue[_indexRSV]);
				_arrayRSActualValues[_indexRSV] = _constantString.Translate();
			}
		}
		PerformOperand<std::string>(_arrayRSActualValues[0],_arrayRSActualValues[1]);
	}
	template<class T> inline void CreateVarAndConst(const size_t possibility) {
		T _arrayRSActualValues[2];
		for(size_t _indexRSV = 0; _indexRSV < 2; _indexRSV++) {
			if(CheckVar(_rsValue[_indexRSV])) {
				RSVVariable<T> _variable(_rsValue[_indexRSV],possibility);
				_arrayRSActualValues[_indexRSV] = _variable.Translate();
			}
			else {
				RSVConst<T> _constant(_rsValue[_indexRSV],possibility);
				_arrayRSActualValues[_indexRSV] = _constant.Translate();
			}
		}
		_condition = PerformOperand<T>(_arrayRSActualValues[0],_arrayRSActualValues[1]);
	}
public:
	std::string _condition = "";
	explicit Condition(void) = default;
 	explicit Condition(const std::string &condition) 
		: _condition(condition) {};
	~Condition(void) {};
	bool Compare(void) {
		GetTypeOfCondition();
		(*this.*_arrayTypeFunctions[_typesOfRSV])();
		return _isConditionTrue;
	}
	void Init(void) {
		GetValueOfFirstCondition();
		GetOperand();
		GetValueOfSecondCondition();

		_arrayTypeFunctions[0] = &Condition::FunctionInt;
		_arrayTypeFunctions[1] = &Condition::FunctionChar;
		_arrayTypeFunctions[2] = &Condition::FunctionBool;
		_arrayTypeFunctions[3] = &Condition::FunctionString;
	}
	void Update(const std::string &condition) {
		_condition = condition;
		_rsValue[0] = "";
		_rsValue[1] = "";
		_index = 1;
		GetValueOfFirstCondition();
		GetValueOfSecondCondition();
	}
};