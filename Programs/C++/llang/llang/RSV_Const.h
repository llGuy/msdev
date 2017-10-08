#ifndef _RSV_CONST
#define _RSV_CONST

#include "Misc.h"
#include "CNSTMacros.h"

#include "Vector.h"
#include "VarHTables.h"
template<typename T>
class RSV_Const {
private:
	//functions depend on what the type
	//of the RSV is
	T M_GetValueOfInt(void) const {
		int l_integer = 0;
		for(size_t l_charIter = 0; l_charIter < m_strRSV.length(); l_charIter++)
			l_integer += (int)(m_strRSV[l_charIter] - 48) * ::G_Power(10,m_strRSV.length() - l_charIter - 1);
		return l_integer;
	}
	T M_GetValueOfChar(void) const { return m_strRSV[1]; };
	T M_GetValueOfBool(void) const { return m_strRSV == "true" ? true : false; };
	T M_DefaultFunction(void) const { return _NULL; };
public:
	explicit RSV_Const(void)
		: m_typeOfRSV(type_default)
	{
		m_possibleFunctions[0] = &RSV_Const<T>::M_GetValueOfInt;
		m_possibleFunctions[1] = &RSV_Const<T>::M_GetValueOfChar;
		m_possibleFunctions[2] = &RSV_Const<T>::M_GetValueOfBool;
		m_possibleFunctions[3] = &RSV_Const<T>::M_DefaultFunction;
	}
	explicit RSV_Const(const std::string& p_strRSV,type p_typeOfRSV)
		: m_strRSV(p_strRSV),m_typeOfRSV(p_typeOfRSV)
	{
		m_possibleFunctions[0] = &RSV_Const<T>::M_GetValueOfInt;
		m_possibleFunctions[1] = &RSV_Const<T>::M_GetValueOfChar;
		m_possibleFunctions[2] = &RSV_Const<T>::M_GetValueOfBool;
		m_possibleFunctions[3] = &RSV_Const<T>::M_DefaultFunction;
	}
public:
	//function that will be called by the line of code
	T M_GetValueOfRSV(void) { return (*this.*m_possibleFunctions[m_typeOfRSV])(); };
private:
	type m_typeOfRSV;
	std::string m_strRSV;
	typedef T(RSV_Const<T>::*func_ptr)(void) const;
	func_ptr m_possibleFunctions[4];
};
#endif
