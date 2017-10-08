#ifndef _RSV_OPERATION
#define _RSV_OPERATION

#include "Misc.h"
#include "Calculator_Parser.h"

class RSV_Operation {
public:
	explicit RSV_Operation(const std::string& p_strRSV)
		: m_strRSV(p_strRSV)
	{
	}
	~RSV_Operation(void)
	{
	}
public:
	size_t M_GetValueOfOperation(void) const {
		Parser l_parserOfOperation(m_strRSV);
		return l_parserOfOperation.M_Calculate();
	}
private:
	std::string m_strRSV;
};

#endif