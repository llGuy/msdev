#ifndef _REGS_TOKENIZER_HEADER
#define _REGS_TOKENIZER_HEADER

#include <vector>

/*

	fill hoth with [value or register] you must

*/

namespace sw_lang {
	namespace tk {
		class Regs_Tk {
		public:
			//tokenizes fill instructions
			static std::vector<std::string> M_Tok(const std::string& p_fill) {
				std::vector<std::string> l_tokVec;
				std::size_t l_strIter = 0;
				std::string l_tempTok;
				while(l_tokVec.size() < 6) {
					if(p_fill[l_strIter] == ' ' || p_fill[l_strIter] == '\0') {
						l_tokVec.push_back(l_tempTok);
						l_tempTok = "";
					}
					else l_tempTok += p_fill[l_strIter];
					++l_strIter;
				}
				return l_tokVec;
			}
		};
	}
}

#endif