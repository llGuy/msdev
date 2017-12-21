#ifndef _PARSER_HEADER
#define _PARSER_HEADER

#include <iostream>
#include <string>

#include "../grammar/include.h"

//simply just tells the compiler what type of instruction 
//the line represents
namespace sw_lang {
	namespace prs {
		class Parser {
		public:
			enum instr_t {
				arith_t = 0,
				fill_t = 1,
				show_t = 2,
				default_t = 3
			};
		public:
			static bool M_IsArith(const std::string& p_tkKey) {
				//m_arrWS[5];
				bool l_isArith = false;
				std::size_t l_arrIter = 0;
				while(!l_isArith && l_arrIter < 5) {
					l_isArith = p_tkKey == *gr::Arith_Gr::m_arrWS[l_arrIter];
					if(l_isArith) return true;
					++l_arrIter;
				}
				return false;
			}
			static instr_t M_Parse(const std::string& p_tkKey) {
				if(Parser::M_IsArith(p_tkKey)) 
					return arith_t;
				
				else if(p_tkKey == "fill") 
					return fill_t;
				
				else if(p_tkKey == "show") 
					return show_t; 

				else return default_t;
			}
		};
	}
}

#endif