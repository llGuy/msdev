#ifndef _INPUT
#define _INPUT

#include "Misc.h"
#include "IncludeRSV.h"

namespace CLine {
	class LineOfCode_Input : public LineOfCode {
	public:
		explicit LineOfCode_Input(const std::string& p_lineStr)
			: m_lineStr(p_lineStr)
		{
		}
	private:
		void M_GetRSVStr(void) {
			size_t l_lineStrIter = 6;
			m_RSVStr = ::G_BuildString(';',l_lineStrIter,m_lineStr);
		}
		void M_GetTypeOfRSV(void) { m_typeOfRSV = ::G_FetchTypeOfVar(m_RSVStr); };
	public:
		void M_Translate(void) override {
			M_GetRSVStr();
			M_GetTypeOfRSV();

			auto l_inpSzet = [&](void)->void {std::cin >> VarHT::M_Shared().m_hTableOfSzet.M_FindVariable(m_RSVStr)->m_value; };
			auto l_inpChar = [&](void)->void {std::cin >> VarHT::M_Shared().m_hTableOfChar.M_FindVariable(m_RSVStr)->m_value; };
			auto l_inpBool = [&](void)->void {std::cin >> VarHT::M_Shared().m_hTableOfBool.M_FindVariable(m_RSVStr)->m_value; };
			auto l_inpStr = [&](void)->void {std::getline(std::cin, VarHT::M_Shared().m_hTableOfStr.M_FindVariable(m_RSVStr)->m_value); };
			std::unordered_map<type,std::function<void(void)>> l_mapOfTypesInp;
			l_mapOfTypesInp[type_int] = l_inpSzet;
			l_mapOfTypesInp[type_char] = l_inpChar;
			l_mapOfTypesInp[type_bool] = l_inpBool;
			l_mapOfTypesInp[type_str] = l_inpStr;

			for(auto l_mapIter = l_mapOfTypesInp.begin(); l_mapIter != l_mapOfTypesInp.end(); ++l_mapIter) {
				if(l_mapIter->first == m_typeOfRSV) {
					l_mapIter->second();
					break;
				}
			}
		}
	private:
		std::string m_lineStr;
		std::string m_RSVStr;
		type m_typeOfRSV;
	};
}
#endif