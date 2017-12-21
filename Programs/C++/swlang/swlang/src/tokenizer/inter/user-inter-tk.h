#ifndef _USER_INTER_TOKENIZER_HEADER
#define _USER_INTER_TOKENIZER_HEADER

#include <vector>
#include <iostream>
#include <string>

/*

	show user [value of string] you must

*/

namespace sw_lang {
	namespace tk {
		class UserIter_Tk {
		public:
			//needs to make sure that it keeps all strings
			//as one token and doesn't separate the strings
			//into different tokens where there are spaces
			//e.g. "hello world" : makes sure that "hello world"
			//is one token despite the spaces
			static std::vector<std::string> M_Tok(const std::string& p_print) {
				std::vector<std::string> l_tokVec;
				std::size_t l_strIter = 0;
				std::string l_tempTok;
				bool l_isStr = false;
				while(l_tokVec.size() < 5) {
					if((p_print[l_strIter] == ' ' || p_print[l_strIter] == '\0') && !l_isStr) {
						l_tokVec.push_back(l_tempTok);
						l_tempTok = "";
					}
					else l_tempTok += p_print[l_strIter];
					if(p_print[l_strIter] == '\"' && !l_isStr) {
						l_isStr = true;
						++l_strIter;
						continue;
					}
					if(p_print[l_strIter] == '\"' && l_isStr) 
						l_isStr = false;
					++l_strIter;
				}
				return l_tokVec;
			}
		};
	}
}

#endif