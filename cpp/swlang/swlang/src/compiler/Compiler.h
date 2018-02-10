#ifndef _COMPILER_HEADER
#define _COMPILER_HEADER

#include <fstream>
#include <iostream>
#include <string>

#include "../grammar/include.h"
#include "../instr/include.h"
#include "../tokenizer/include.h"
#include "../parser/parser.h"
#include "../misc.h"

namespace sw_lang {
	namespace cmpl {
		class Compiler {
		public:
			explicit Compiler(std::fstream& p_stream)
			{
				while(p_stream) {
					//extracts all the executable lines of code
					std::string l_tempLine;
					std::getline(p_stream,l_tempLine);

					if(l_tempLine != "" && l_tempLine[0] != '#') {
						size_t l_index = 0;
						std::string l_actualLine = "";
						while(l_tempLine[l_index] == ' ')
							l_index++;
						//gets rid of spaces before the actual line
						l_actualLine = l_tempLine.substr(l_index);
						m_vecLineStr.push_back(l_actualLine);
					}
				}
				//the first line will be "in a galaxy far far away"
				//the last line will be "may the force be with you"
				std::string l_startLine = m_vecLineStr[0];
				std::string l_endLine = m_vecLineStr[m_vecLineStr.size() - 1];
				m_vecLineStr.erase(m_vecLineStr.begin());
				m_vecLineStr.erase(m_vecLineStr.end() - 1);
				if(l_startLine != "in a galaxy, far far away") {
					std::cerr << "failed to compile, galaxy unspecified\n";
					throw 1;
				}
				if(l_endLine != "may the force be with you") {
					std::cerr << "that's a little rude\n";
					throw 1;
				}
				//initializes the map containing the different arithmetic functions that one can use
				instr::Arith_Instr::M_InitMap();
			}
		private:
			//function used for checking the syntax
			//to make sure the program is ready to be executed
			const bool M_GrCheck(const prs::Parser::instr_t p_instrT,const std::vector<std::string>& p_vecTk) {
				if(p_instrT == prs::Parser::arith_t) return gr::Arith_Gr::M_GrCheck(p_vecTk);
				else if(p_instrT == prs::Parser::show_t) return gr::Inter_Gr::M_GrCheck(p_vecTk);
				else if(p_instrT == prs::Parser::fill_t) return gr::Regs_Gr::M_GrCheck(p_vecTk);
				else return false;
			}
			//tokenizes all the instructions and initializes the instruction objects
			const bool M_BuildInstrs(void) {
				for(std::size_t l_vecIter = 0; l_vecIter < m_vecLineStr.size(); ++l_vecIter) {
					std::string l_frstWord = G_GetFirstToken(m_vecLineStr[l_vecIter]);
					prs::Parser::instr_t l_instrT = prs::Parser::M_Parse(l_frstWord);
					if(l_instrT == prs::Parser::arith_t) {
						std::vector<std::string> l_vecTok(tk::Arith_Tk::M_Tok(m_vecLineStr[l_vecIter]));
						if(!M_GrCheck(prs::Parser::arith_t,l_vecTok)) return false;
						m_instrVec.push_back(new instr::Arith_Instr(l_vecTok));
					}
					else if(l_instrT == prs::Parser::fill_t) {
						std::vector<std::string> l_vecTok(tk::Regs_Tk::M_Tok(m_vecLineStr[l_vecIter]));
						if(!M_GrCheck(prs::Parser::fill_t,l_vecTok)) return false;
						m_instrVec.push_back(new instr::Regs_Instr(l_vecTok));
					}
					else if(l_instrT == prs::Parser::show_t) {
						std::vector<std::string> l_vecTok(tk::UserIter_Tk::M_Tok(m_vecLineStr[l_vecIter]));
						if(!M_GrCheck(prs::Parser::show_t,l_vecTok)) return false;
						m_instrVec.push_back(new instr::Print_Instr(l_vecTok));
					}
					//incorrect syntax
					else return false;
				}
				//correct syntax : ready to be executed
				return true;
			}
		public:
			//main instruction
			const bool M_ExecuteInstrs(void) {
				if(!M_BuildInstrs()) return false;
				//executes every instruction in order
				for(auto& p_vecIter : m_instrVec) 
					p_vecIter->M_Execute();
				//must always be polite 
				std::cout << "\nand may the force be with you too\n\n";
				//no problems occured
				return true;
			} 
		private:
			std::vector<std::string> m_vecLineStr;
			std::vector<instr::Instr_Base*> m_instrVec;
			std::vector<prs::Parser::instr_t> m_instrTVec;
		};
	}
}


#endif