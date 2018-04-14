#ifndef _ARITH_TK_HEADER
#define _ARITH_TK_HEADER

#include <string>
#include <vector>
#include <iostream>

namespace sw_lang {
	namespace tk {
		class Arith_Tk {
		public:
			//simply separates each token that is 
			//separated by a space
			static std::vector<std::string> M_Tok(const std::string& p_arith) {
				std::vector<std::string> l_tokVec;
				std::size_t l_strIter = 0;
				std::string l_tempTok;
				while(l_tokVec.size() < 3) {
					if(p_arith[l_strIter] == ' ' || p_arith[l_strIter] == '\0') {
						l_tokVec.push_back(l_tempTok);
						l_tempTok = "";
					}
					else l_tempTok += p_arith[l_strIter];
					++l_strIter;
				}
				return l_tokVec;
			}
		};
	}
}

#endif
