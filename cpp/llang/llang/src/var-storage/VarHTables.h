#ifndef _VARHTABLES
#define _VARHTABLES

#include "../misc/CNSTMacros.h"
#include "dat-struct/HTable.h"

class VarHT {
public:
	htble::HTable<size_t> m_hTableOfSzet;
	htble::HTable<char> m_hTableOfChar;
	htble::HTable<bool>m_hTableOfBool;
	htble::HTable<std::string> m_hTableOfStr;

public:
	static VarHT& M_Shared(void) {
		static VarHT* l_globVarHT = nullptr;
		if(l_globVarHT == nullptr)
			l_globVarHT = new VarHT();
		return *l_globVarHT;
	}
private:
	explicit VarHT()
	{
	}
};

#endif