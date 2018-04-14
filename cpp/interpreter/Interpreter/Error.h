#pragma once
#include <iostream>
#include <string>
class Error {
public:
	Error(void) {};
	~Error(void) {};
	size_t _id;
};
class SyntaxError : public Error {
private:
	std::string _incorrect = "";
	std::string _correct = "";
	std::string _comment = "";
public:
	explicit SyntaxError(const std::string &incorrect,const std::string &correct, const std::string &comment = "") 
		: _incorrect(incorrect),_correct(correct),_comment(comment){};
	~SyntaxError(void) {};
	void ThrowException(void) {
		if(_comment != "") {
			std::cout << "ERROR(1) incorrect syntax: ";
			std::cout << _comment << std::endl;
			return;
		}
		else {
			std::cout << "ERROR(1) incorrect syntax: ";
			std::cout << "\"" << _incorrect << "\"" << " -> " << "\"" << _correct << "\"" << std::endl;
			return;
		}
	}
};
class UndeclaredVariable : public Error {
private:
	std::string _undeclaredVariable = "";
public:
	explicit UndeclaredVariable(const std::string &undVar) 
		: _undeclaredVariable(undVar) {};
	~UndeclaredVariable(void) {};
	void ThrowExeption(void) {
		std::cout << "ERROR(2) undeclared variable: \"";
		std::cout << _undeclaredVariable << "\"" << std::endl;
	}
};
class IncorrectTypeConversion : public Error {
private:
	std::string _comment;
public:
	explicit IncorrectTypeConversion(void) = default;
	explicit IncorrectTypeConversion(const std::string &comment)
		: _comment(comment) {};
	explicit IncorrectTypeConversion(const std::string &&comment)
		: _comment(comment) {};
	~IncorrectTypeConversion(void) {};
	void ThrowException(void) {
		std::cout << "ERROR(3) incorrect type conversion: \n";
		std::cout << _comment << std::endl;
	}
};