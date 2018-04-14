#ifndef _ARITH_GR_HEADER
#define _ARITH_GR_HEADER

#include <iostream>
#include <string>

#include "../../reg/reg-sing.h"
#include "../../misc.h"

namespace sw_lang {
	namespace gr {
		class Arith_Gr {
		public:
			static const bool M_ArithType(const std::string& p_instrTk) {
				//checks if the given arithmetic
				//function exists
				bool l_grCorrect = false;
				std::size_t l_arrWSIter = 0;
				while(!l_grCorrect && l_arrWSIter < 5) {
					l_grCorrect = p_instrTk == *Arith_Gr::m_arrWS[l_arrWSIter];
					++l_arrWSIter;
				}
				return l_grCorrect;
			} 
			static const bool M_T2(const std::string& p_t2) { return G_IsPlanet(p_t2); };
			static const bool M_T3(const std::string& p_t3) { return G_IsValue(p_t3); };
			static const bool M_GrCheck(const std::vector<std::string>& p_vecTk) {
				bool l_grCorrect = p_vecTk.size() == 3;
				l_grCorrect &= Arith_Gr::M_ArithType(p_vecTk[0]);
				l_grCorrect &= Arith_Gr::M_T2(p_vecTk[1]);
				l_grCorrect &= Arith_Gr::M_T3(p_vecTk[2]);
				return l_grCorrect;
			}
		public:
			static const std::string m_addWS;
			static const std::string m_subWS;
			static const std::string m_mulWS;
			static const std::string m_divWS;
			static const std::string m_modWS;
			static const std::string* m_arrWS[5];
		};
	}
}

#endif