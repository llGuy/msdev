#ifndef _INPUT
#define _INPUT

#include "../../misc/Misc.h"
#include "../../rsv/IncludeRSV.h"

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
			
			InpItm::M_Shared().m_mapInp[m_typeOfRSV](m_RSVStr);
		}
	private:
		std::string m_lineStr;
		std::string m_RSVStr;
		type m_typeOfRSV;
	private:
		struct InpItm {
			std::unordered_map<type,std::function<void(const std::string&)>> m_mapInp;
		public:
			void M_Init(void) {
				m_mapInp[type_int] = [&](const std::string& p_rsv)->void {std::cin >> VarHT::M_Shared().m_hTableOfSzet.M_FindVariable(p_rsv)->M_Val(); };
				m_mapInp[type_char] = [&](const std::string& p_rsv)->void {std::cin >> VarHT::M_Shared().m_hTableOfChar.M_FindVariable(p_rsv)->M_Val(); };
				m_mapInp[type_bool] = [&](const std::string& p_rsv)->void {std::cin >> VarHT::M_Shared().m_hTableOfBool.M_FindVariable(p_rsv)->M_Val(); };
				m_mapInp[type_str] = [&](const std::string& p_rsv)->void {std::getline(std::cin,VarHT::M_Shared().m_hTableOfStr.M_FindVariable(p_rsv)->M_Val()); };
			}
			static InpItm& M_Shared(void) {
				static InpItm* l_singl = nullptr;
				if(l_singl == nullptr) {
					l_singl = new InpItm();
					l_singl->M_Init();
				}
				return *l_singl;
			}
		};
	};
}
#endif