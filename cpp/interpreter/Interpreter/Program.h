#pragma once
#include "CodeLine.h"
#include <unordered_map>
#include <iostream>
#include <fstream>
 

class Program {
private:
	//vector of the lines as strings
	Vector<std::string> _vectorOfStrings;
	//vector of LineOfCode pointers
	Vector<CLine::LineOfCode*> _vectorOfLines;
protected:
	inline Vector<std::string> BuildBody(Vector<std::string> &vec, size_t &index) const {
		Vector<std::string> _vectorWithBody;
		bool _end = false;
		size_t _numBegins = 0;
		size_t _numEnds = 0;
		while(!_end) {
			if(vec[index] == "begin") _numBegins++;
			else if(vec[index] == "end") _numEnds++;

			if(_numBegins == _numEnds && _numBegins > 0) _end = true;
			else {
				_vectorWithBody.PushBack(vec[index]);
				index++;
			}
		}
		return _vectorWithBody;
	}
	inline Vector<std::string> BuildBodyIfStatement(Vector<std::string> &vec,size_t &index) const {
		Vector<std::string> _vectorWithBody;	//only the if statement
		bool _end = false;

		size_t _numOfIfs = 1;
		size_t _numOfEndifs = 0;

		while(!_end) {
			if(GetKeyword(vec[index]) == "if")_numOfIfs++;
			else if(GetKeyword(vec[index]) == "endif")_numOfEndifs++;
			_vectorWithBody.PushBack(vec[index]);
			if(_numOfEndifs == _numOfIfs && _numOfEndifs >= 1) _end = true;
			else index++;
		}
		return _vectorWithBody;
	}
public:
	explicit Program(void) = default;
	explicit Program(std::fstream &stream) {
		while(stream) {
			std::string _temp;
			std::getline(stream,_temp);
			if(_temp != "" && _temp[0] != '#') {
				size_t _index = 0;
				std::string _actualString = "";
				//with spaces
				while(_temp[_index] == ' ') 
					_index++;
				_actualString = _temp.substr(_index);
				_vectorOfStrings.PushBack(_actualString);
			}
		}
	}
	explicit Program(const Vector<std::string> &vecStr) 
		: _vectorOfStrings(vecStr) 
	{
	}
	~Program(void) 
	{
	}
	void Parse(Vector<std::string> &vecStr,Vector<CLine::LineOfCode*> &vecLines) {
		size_t _numOfBegins = 0;
		size_t _numOfEnds = 0;

		auto _beginEndLambda = [&](size_t &index)->void {};
		auto _endifLambda = [&](size_t &index)->void {};

		auto _setLambda = [&](size_t &index)->void { 
			vecLines.PushBack(new CLine::SetLineOfCode(vecStr[index])); };
		auto _modLambda = [&](size_t &index)->void { 
			vecLines.PushBack(new CLine::ModLineOfCode(vecStr[index])); 
		};
		auto _printLambda = [&](size_t &index)->void { 
			vecLines.PushBack(new CLine::PrintLineOfCode(vecStr[index])); };
		auto _printlnLambda = [&](size_t &index)->void {
			vecLines.PushBack(new CLine::PrintlnLineOfCode(vecStr[index])); 
		};
		auto _inputLambda = [&](size_t &index)->void { vecLines.PushBack(new CLine::InputLineOfCode(vecStr[index])); };
		auto _ifStatementLambda = [&](size_t &index)->void { 
			Vector<CLine::LineOfCode*> _vectorOfIfStatement;
			auto _buildFirstIfBodyLam = [&](void)->void {
				_vectorOfIfStatement.PushBack(new CLine::IfLineOfCode(BuildBody(vecStr,index)));
				Parse(*(_vectorOfIfStatement[_vectorOfIfStatement._size - 1]->GetBodyString()),
					*(_vectorOfIfStatement[_vectorOfIfStatement._size - 1]->GetBodyLine()));
			};
			_buildFirstIfBodyLam();
			Vector<std::string> _vectorStrOfIfStatement = BuildBodyIfStatement(vecStr,index);
			Parse(_vectorStrOfIfStatement,_vectorOfIfStatement);
			vecLines.PushBack(new CLine::IfStatement(_vectorOfIfStatement));
		};
		auto _elifLambda = [&](size_t &index)->void {
			vecLines.PushBack(new CLine::ElifLineOfCode(BuildBody(vecStr,index)));
			Parse(*(vecLines[vecLines._size - 1]->GetBodyString()),
				*(vecLines[vecLines._size - 1]->GetBodyLine()));
		};
		auto _elseLambda = [&](size_t &index)->void {
			vecLines.PushBack(new CLine::ElseLineOfCode(BuildBody(vecStr,index)));
			Parse(*(vecLines[vecLines._size - 1]->GetBodyString()),
				*(vecLines[vecLines._size - 1]->GetBodyLine()));
		};
		auto _forLambda = [&](size_t &index)->void {
			vecLines.PushBack(new CLine::ForLineOfCode(BuildBody(vecStr,index)));
			Parse(*(vecLines[vecLines._size - 1]->GetBodyString()),
				*(vecLines[vecLines._size - 1]->GetBodyLine()));
		};
		auto _whileLambda = [&](size_t &index)->void {
			vecLines.PushBack(new CLine::WhileLineOfCode(BuildBody(vecStr,index)));
			Parse(*(vecLines[vecLines._size - 1]->GetBodyString()),
				*(vecLines[vecLines._size - 1]->GetBodyLine()));
		};
		auto _saveLambda = [&](size_t &index)->void { vecLines.PushBack(new CLine::SaveLineOfCode(vecStr[index])); };
		auto _readLambda = [&](size_t &index)->void {vecLines.PushBack(new CLine::ReadLineOfCode(vecStr[index])); };

		std::unordered_map<std::string,std::function<void(size_t&)>> _mapOfLinesLambdas;

		_mapOfLinesLambdas["begin"] = _beginEndLambda;
		_mapOfLinesLambdas["end"] = _beginEndLambda;
		_mapOfLinesLambdas["endif"] = _beginEndLambda;
		_mapOfLinesLambdas["set"] = _setLambda;
		_mapOfLinesLambdas["mod"] = _modLambda;
		_mapOfLinesLambdas["print"] = _printLambda;
		_mapOfLinesLambdas["println"] = _printlnLambda;
		_mapOfLinesLambdas["input"] = _inputLambda;
		_mapOfLinesLambdas["if"] = _ifStatementLambda;
		_mapOfLinesLambdas["else"] = _elseLambda;
		_mapOfLinesLambdas["elif"] = _elifLambda;
		_mapOfLinesLambdas["for"] = _forLambda;
		_mapOfLinesLambdas["while"] = _whileLambda;
		_mapOfLinesLambdas["save"] = _saveLambda;
		_mapOfLinesLambdas["read"] = _readLambda;
		//_mapOfLinesLambdas["encrypt"] = /*_encLambda*/;

		for(size_t _index = 0; _index < vecStr._size; _index++) {
			std::string _keyword = GetKeyword(vecStr[_index]);
			_mapOfLinesLambdas[GetKeyword(vecStr[_index])](_index);
		}
	}
	void ExecuteProgram(void) {
		Parse(_vectorOfStrings,_vectorOfLines);
		for(size_t _index = 0; _index < _vectorOfLines._size; _index++) {
			std::string _debug = _vectorOfLines[_index]->_lineOfCode;
			_vectorOfLines[_index]->TranslateToCPP();
		}
	}
};