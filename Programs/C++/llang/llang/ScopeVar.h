#ifndef _SCOPEVAR
#define _SCOPEVAR

#include "Misc.h"
#include "IncludeCLine.h"

class ScopeVar {
public:
	explicit ScopeVar(void)
	{
	}
	explicit ScopeVar(CLine::LineOfCode* p_setLine)
		: m_nameStr(p_setLine->M_GetNameStr()),m_typeStr(p_setLine->M_GetTypeStr())
	{
	}
	~ScopeVar(void) 
	{
	}
public:
	void M_Delete(void) const {
		auto l_delSzet = [&](void)->void {VarHT::M_Shared().m_hTableOfSzet.M_Delete(m_nameStr); };
		auto l_delChar = [&](void)->void {VarHT::M_Shared().m_hTableOfChar.M_Delete(m_nameStr); };
		auto l_delBool = [&](void)->void {VarHT::M_Shared().m_hTableOfBool.M_Delete(m_nameStr); };
		auto l_delStr = [&](void)->void {VarHT::M_Shared().m_hTableOfStr.M_Delete(m_nameStr); };

		std::unordered_map<char*,std::function<void(void)>> l_mapOfDelLam;
		l_mapOfDelLam["int"] = l_delSzet;
		l_mapOfDelLam["char"] = l_delChar;
		l_mapOfDelLam["bool"] = l_delBool;
		l_mapOfDelLam["string"] = l_delStr;
		for(auto l_lamIter = l_mapOfDelLam.begin(); l_lamIter != l_mapOfDelLam.end(); ++l_lamIter) {
			if(l_lamIter->first == m_typeStr) {
				l_lamIter->second();
				return;
			}
		}
	}
private:
	std::string m_nameStr;
	std::string m_typeStr;
};

#endif