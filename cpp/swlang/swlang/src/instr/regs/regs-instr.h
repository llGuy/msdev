#ifndef _REG_INSTR_HEADER
#define _REG_INSTR_HEADER

#include "../instr.h"
#include "../../reg/reg-sing.h"

#include <vector>
#include <iostream>
#include <sstream>

namespace sw_lang {
	namespace instr {
		class Regs_Instr : public Instr_Base {
		public:
			explicit Regs_Instr(const std::vector<std::string>& p_tkVec)
				: m_destPlanet(p_tkVec[1]),m_val(p_tkVec[3])
			{
			}
		public:
			void M_Execute(void) override {
				//simply just fills the register(address in memory)
				//with a given value (either a planet or a number)
				int l_val;
				std::stringstream l_ss(m_val);
				l_ss >> l_val;
				int* l_planetPtr = rs::Regs::M_Shared().m_strPlanetMap[m_destPlanet]->m_regPtr;
				*l_planetPtr = l_val;
			}
		private:
			std::string m_destPlanet;
			std::string m_val;
		};
	}
}

#endif