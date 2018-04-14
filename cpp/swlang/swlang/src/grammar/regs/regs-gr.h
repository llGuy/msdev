#ifndef _REGS_GRAMMAR_HEADER
#define _REGS_GRAMMAR_HEADER

#include <iostream>
#include <string>
#include <vector>

#include "../../reg/reg-sing.h"
#include "../../misc.h"
namespace sw_lang {
	namespace gr {
		class Regs_Gr {
		public:
			static const bool M_T1(const std::string& p_t1) { return p_t1 == "fill"; };
			static const bool M_DestPlanet(const std::string& p_t2) { return G_IsPlanet(p_t2); };
			static const bool M_T3(const std::string& p_t3) { return p_t3 == "with"; };
			static const bool M_Value(const std::string& p_t4) { return G_IsValue(p_t4); };
			static const bool M_T5(const std::string& p_t5) { return p_t5 == "you"; };
			static const bool M_T6(const std::string& p_t6) { return p_t6 == "must"; };
			static const bool M_GrCheck(const std::vector<std::string>& p_vecTk) {
				bool l_correct = p_vecTk.size() == 6;
				l_correct &= Regs_Gr::M_T1(p_vecTk[0]);
				l_correct &= Regs_Gr::M_DestPlanet(p_vecTk[1]);
				l_correct &= Regs_Gr::M_T3(p_vecTk[2]);
				l_correct &= Regs_Gr::M_Value(p_vecTk[3]);
				l_correct &= Regs_Gr::M_T5(p_vecTk[4]);
				l_correct &= Regs_Gr::M_T6(p_vecTk[5]);
				return l_correct;
			}
		};
	}
}

#endif