#ifndef _INTERFACE_HEADER
#define _INTERFACE_HEADER

#include <iostream>
#include <string>
#include <vector>

#include "../../reg/reg-sing.h"
#include "../../misc.h"

namespace sw_lang {
	namespace gr {
		class Inter_Gr {
		public:
			static const bool M_T1(const std::string& p_t1) { return p_t1 == "show"; };
			static const bool M_T2(const std::string& p_t2) { return p_t2 == "earthman"; };
			static const bool M_Itm(const std::string& p_itm) { return G_IsValue(p_itm) || G_IsStr(p_itm); };
			static const bool M_T4(const std::string& p_t4) { return p_t4 == "you"; };
			static const bool M_T5(const std::string& p_t5) { return p_t5 == "must"; };
			static const bool M_GrCheck(const std::vector<std::string>& p_vec) {
				bool l_grCorrect = p_vec.size() == 5;
				l_grCorrect &= Inter_Gr::M_T1(p_vec[0]);
				l_grCorrect &= Inter_Gr::M_T2(p_vec[1]);
				l_grCorrect &= Inter_Gr::M_Itm(p_vec[2]);
				l_grCorrect &= Inter_Gr::M_T4(p_vec[3]);
				l_grCorrect &= Inter_Gr::M_T5(p_vec[4]);
				return l_grCorrect;
			}
		};
	}
}

#endif