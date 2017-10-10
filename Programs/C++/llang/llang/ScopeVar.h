#ifndef _SCOPEVAR
#define _SCOPEVAR

#include "Misc.h"

class ScopeVar {
public:
	explicit ScopeVar(void)
	{
	}
	~ScopeVar(void) 
	{
	}
public:
	void M_Update(CLine::LineOfCode* p_line) {
		m_nameStr = p_line->M_GetNameStr();
		m_typeStr = p_line->M_GetTypeStr();
	}
	void M_Delete(void) const {
		auto l_delSzet = [&](void)->void {
			VarHT::M_Shared().m_hTableOfSzet.M_Delete(m_nameStr); };
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