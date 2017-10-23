#ifndef _RSV_VAR
#define _RSV_VAR

#include "Misc.h"
#include "CNSTMacros.h"

#include "Vector.h"
#include "VarHTables.h"

template<typename T>
class RSV_Variable {
protected:
	T M_FetchValueOfSzetVar(void) const { return (T)VarHT::M_Shared().m_hTableOfSzet.M_FindVariable(m_strRSV)->M_Val(); };
	T M_FetchValueOfCharVar(void) const { return (T)VarHT::M_Shared().m_hTableOfChar.M_FindVariable(m_strRSV)->M_Val(); };
	T M_FetchValueOfBoolVar(void) const { return (T)VarHT::M_Shared().m_hTableOfBool.M_FindVariable(m_strRSV)->M_Val(); };
	T M_DefaultFunction(void) const { return _NULL; };
public:
	explicit RSV_Variable(void) 
		: m_typeOfRSV(type_default)
	{
		m_possibleFunctions[0] = &RSV_Variable<T>::M_FetchValueOfSzetVar;
		m_possibleFunctions[1] = &RSV_Variable<T>::M_FetchValueOfCharVar;
		m_possibleFunctions[2] = &RSV_Variable<T>::M_FetchValueOfBoolVar;
		m_possibleFunctions[3] = &RSV_Variable<T>::M_DefaultFunction;
	}
	explicit RSV_Variable(const std::string& p_strRSV,type p_typeOfRSV)
		: m_strRSV(p_strRSV),m_typeOfRSV(p_typeOfRSV)
	{
		m_possibleFunctions[0] = &RSV_Variable<T>::M_FetchValueOfSzetVar;
		m_possibleFunctions[1] = &RSV_Variable<T>::M_FetchValueOfCharVar;
		m_possibleFunctions[2] = &RSV_Variable<T>::M_FetchValueOfBoolVar;
		m_possibleFunctions[3] = &RSV_Variable<T>::M_DefaultFunction;
	}
public:
	T M_GetValOfVar(void) const { return (*this.*m_possibleFunctions[m_typeOfRSV])(); };
private:
	type m_typeOfRSV;
	std::string m_strRSV;
	typedef T(RSV_Variable<T>::*func_ptr)(void) const;
	func_ptr m_possibleFunctions[4];
};

#endif