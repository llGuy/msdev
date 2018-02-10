#ifndef _MISC_HEADER
#define _MISC_HEADER

#include <iostream>
#include <string>

#include "reg/reg-sing.h"

namespace sw_lang {
	inline const bool G_IsNumber(const std::string& p_tk) noexcept {
		bool l_grCorrect = true;
		std::size_t l_t2Iter = 0;
		while(l_grCorrect && l_t2Iter < p_tk.length()) {
			l_grCorrect = (p_tk[l_t2Iter] >= 48) && (p_tk[l_t2Iter] <= 57);
			++l_t2Iter;
		}
		return l_grCorrect;
	}
	inline const bool G_IsPlanet(const std::string& p_tk) noexcept {
		bool l_grCorrect = false;
		for(auto l_iter = rs::Regs::M_Shared().m_strPlanetMap.begin();
			l_iter != rs::Regs::M_Shared().m_strPlanetMap.end(); ++l_iter) {
			l_grCorrect = p_tk == l_iter->first;
			if(l_grCorrect) return true;
			else continue;
		}
		return false;
	}
	//isValue means : is a number or a planet / register
	inline const bool G_IsValue(const std::string& p_tk) noexcept {
		bool l_grCorrect = G_IsPlanet(p_tk);
		if(l_grCorrect) return true;
		l_grCorrect = G_IsNumber(p_tk);
		return l_grCorrect;
	}
	inline const bool G_IsStr(const std::string& p_tk) noexcept {
		return p_tk[0] == '\"' && p_tk[p_tk.length() - 1] == '\"';
	}
	inline std::string G_GetFirstToken(const std::string& p_str) noexcept {
		std::size_t l_index = 0;
		std::string l_newStr;
		while(p_str[l_index] != ' ') {
			l_newStr += p_str[l_index];
			++l_index;
		}
		return l_newStr; 
	}
}

#endif