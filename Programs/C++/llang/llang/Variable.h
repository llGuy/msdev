#ifndef _VAR
#define _VAR
#include "CNSTMacros.h"

#include <iostream>

#ifdef OLD
template<typename T>
class Variable {
public:
	T m_value;
	std::string m_name;
	Variable<T>* m_ptrNextVar;
	bool m_isEndOfList;
public:
	explicit Variable(void)
		: m_name(_STR_NULL),m_ptrNextVar(nullptr),m_isEndOfList(false)
	{
	}
	~Variable(void) { delete m_ptrNextVar; };
	void operator=(T p_newVal) { m_value =  p_newVal; };
	friend std::ostream& operator<<(std::ostream& p_stream,Variable<T>& p_var) {
		p_stream << p_var.m_value;
		return p_stream;
	}
};
#endif
#endif
