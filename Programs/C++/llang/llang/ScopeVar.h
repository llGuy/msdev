#ifndef _SCOPEVAR
#define _SCOPEVAR

#include "Misc.h"

//class deletes variables when they are out of scope
class ScopeVar {
public:
	explicit ScopeVar(void)
	{
	}
	~ScopeVar(void) 
	{
	}
public:
	//updates with a LineOfCode*
	//and uses its name and type to know how to delete it
	void M_Update(CLine::LineOfCode* p_line) {
		m_nameStr = p_line->M_GetNameStr();
		m_typeStr = p_line->M_GetTypeStr();
	}
	//unordered_map indexes via a type and 
	//returns a lambda which takes a name and
	//deletes that variable at the HTable of that type
	void M_Delete(void) const { Del::M_Shared().m_mapDelLam[m_typeStr](m_nameStr); }
private:
	std::string m_nameStr;
	std::string m_typeStr;
private:
	struct Del {
		std::unordered_map<std::string,std::function<void(const std::string&)>> m_mapDelLam;
	public:
		static Del& M_Shared(void) {
			static Del* l_singl = nullptr;
			if(l_singl == nullptr) {
				l_singl = new Del();
				l_singl->M_Init();
			}
			return *l_singl;
		}
		void M_Init(void) {
			m_mapDelLam["int"] = [&](const std::string& p_nameStr)->void { VarHT::M_Shared().m_hTableOfSzet.M_Delete(p_nameStr); };
			m_mapDelLam["char"] = [&](const std::string& p_nameStr)->void { VarHT::M_Shared().m_hTableOfChar.M_Delete(p_nameStr); };
			m_mapDelLam["bool"] = [&](const std::string& p_nameStr)->void { VarHT::M_Shared().m_hTableOfBool.M_Delete(p_nameStr); };
			m_mapDelLam["string"] = [&](const std::string& p_nameStr)->void { VarHT::M_Shared().m_hTableOfStr.M_Delete(p_nameStr); };
		}
	};
};

#endif