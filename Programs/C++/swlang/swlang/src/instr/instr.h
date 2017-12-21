#ifndef _INSTR_HEADER
#define _INSTR_HEADER

#include <sstream>
#include <string>

namespace sw_lang {
	namespace instr {
		class Instr_Base {
		public:
			virtual void M_Execute(void) = 0;
			static int M_StrToInt(const std::string& p_inp) {
				int l_val;
				std::stringstream l_ss(p_inp);
				l_ss >> l_val;
				return l_val;
			}
		};
	}
}

#endif