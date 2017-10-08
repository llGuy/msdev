#ifndef _RSV_STRING
#define _RSV_STRING

#include "VarHTables.h"

class RSV_String {
public:
	explicit RSV_String(const std::string& p_strRSV,bool p_isVar)
		: m_strRSV(p_strRSV),m_isVariable(p_isVar)
	{
	}
	~RSV_String(void)
	{
	}
public:
	std::string M_GetValue(void) const {
		if(m_isVariable) 
			return M_FetchVariable();
		else return M_GetValueOfConst();
	}
private:
	std::string M_FetchVariable(void) const { return VarHT::M_Shared().m_hTableOfStr.M_FindVariable(m_strRSV)->m_value; };
	std::string M_GetValueOfConst(void) const {
		size_t l_index = 1;
		std::string l_actualValueOfConst;
		while(m_strRSV[l_index] != '\"') {
			l_actualValueOfConst += m_strRSV[l_index];
			l_index++;
		}
		return l_actualValueOfConst;
	}
private:
	bool m_isVariable;
	std::string m_strRSV;
};

#endif