#ifndef _USER_INTERFACE_INSTRUCTION_HEADER
#define _USER_INTERFACE_INSTRUCTION_HEADER

#include "../include.h"
#include "../instr.h"

//shows the user a value or string
namespace sw_lang {
	namespace instr {
		class Print_Instr : public Instr_Base {
		public:
			explicit Print_Instr(const std::vector<std::string>& p_vec) 
				: m_val(p_vec[2])
			{
			}
		public:
			inline std::string* M_CheckAndGetString(std::string* p_val) {
				if(G_IsStr(*p_val)) return p_val;
				else return nullptr;
			}
			inline void M_PrintStr(void) {
				std::size_t l_integPart = 1;
				std::string l_strVal;
				while(l_integPart < m_val.length() - 1) {
					l_strVal += m_val[l_integPart];
					++l_integPart;
				}
				std::cout << l_strVal;
			}
		public:
			void M_Execute(void) override {
				if(M_CheckAndGetString(&m_val)) M_PrintStr(); 
				else {
					if(G_IsPlanet(m_val)) {
						int l_val = *rs::Regs::M_Shared().m_strPlanetMap[m_val]->m_regPtr;
						std::cout << l_val;
					}
					else {
						int l_val = Print_Instr::M_StrToInt(m_val);
						std::cout << l_val;
					}
				}
				std::cout << std::endl;
			}
		private:
			std::string m_val;
		};
	}
}

#endif