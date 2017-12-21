#ifndef _ARITHMETIC_INSTRUCTION_HEADER
#define _ARITHMETIC_INSTRUCTION_HEADER

#include "../instr.h"
#include "../../reg/reg-sing.h"
#include "../../grammar/arith/arith_gr.h"

#include <vector>
#include <sstream>
#include <unordered_map>

namespace sw_lang {
	namespace instr {
		class Arith_Instr : public Instr_Base {
		public:
			explicit Arith_Instr(const std::vector<std::string>& p_tk) 
				: m_arithStr(p_tk[0]),m_planetDest(p_tk[1]),m_valStr(p_tk[2])
			{
			}
		public:
			void M_Execute(void) override {
				std::string m_planetAndVal[] = {m_planetDest,m_valStr};
				Arith_Instr::m_mapInstr[m_arithStr]->M_Exe(m_planetAndVal);
			}
		public:
			static void M_InitMap(void) {
				static bool l_initialized = false;
				if(!l_initialized) {
					l_initialized = true;
					Arith_Instr::m_mapInstr[gr::Arith_Gr::m_addWS] = new A_Add();
					Arith_Instr::m_mapInstr[gr::Arith_Gr::m_subWS] = new A_Sub();
					Arith_Instr::m_mapInstr[gr::Arith_Gr::m_mulWS] = new A_Mul();
					Arith_Instr::m_mapInstr[gr::Arith_Gr::m_divWS] = new A_Div();
					Arith_Instr::m_mapInstr[gr::Arith_Gr::m_modWS] = new A_Mod();
				}
			}
		private:
			struct A_Arith { virtual void M_Exe(std::string[2]) = 0; };
			struct A_Add : public A_Arith {
				void M_Exe(std::string p_inps[]) override {
					std::string l_planetDest = p_inps[0];
					std::string l_valStr = p_inps[1];
					int* l_planetPtr = rs::Regs::M_Shared().m_strPlanetMap[p_inps[0]]->m_regPtr;
					int l_actualVal;
					if(G_IsPlanet(l_valStr))
						l_actualVal = *rs::Regs::M_Shared().m_strPlanetMap[l_valStr]->m_regPtr;
					else l_actualVal = Arith_Instr::M_StrToInt(l_valStr);
					*l_planetPtr += l_actualVal;
				}
			};
			struct A_Sub : public A_Arith {
				void M_Exe(std::string p_inps[]) override {
					std::string l_planetDest = p_inps[0];
					std::string l_valStr = p_inps[1];
					int* l_planetPtr = rs::Regs::M_Shared().m_strPlanetMap[p_inps[0]]->m_regPtr;
					int l_actualVal;
					if(G_IsPlanet(l_valStr))
						l_actualVal = *rs::Regs::M_Shared().m_strPlanetMap[l_valStr]->m_regPtr;
					else l_actualVal = Arith_Instr::M_StrToInt(l_valStr);
					*l_planetPtr -= l_actualVal;
				}
			};
			struct A_Mul : public A_Arith {
				void M_Exe(std::string p_inps[]) override {
					std::string l_planetDest = p_inps[0];
					std::string l_valStr = p_inps[1];
					int* l_planetPtr = rs::Regs::M_Shared().m_strPlanetMap[p_inps[0]]->m_regPtr;
					int l_actualVal;
					if(G_IsPlanet(l_valStr))
						l_actualVal = *rs::Regs::M_Shared().m_strPlanetMap[l_valStr]->m_regPtr;
					else l_actualVal = Arith_Instr::M_StrToInt(l_valStr);
					*l_planetPtr *= l_actualVal;
				}
			};
			struct A_Div : public A_Arith {
				void M_Exe(std::string p_inps[]) override {
					std::string l_planetDest = p_inps[0];
					std::string l_valStr = p_inps[1];
					int* l_planetPtr = rs::Regs::M_Shared().m_strPlanetMap[p_inps[0]]->m_regPtr;
					int l_actualVal;
					if(G_IsPlanet(l_valStr))
						l_actualVal = *rs::Regs::M_Shared().m_strPlanetMap[l_valStr]->m_regPtr;
					else l_actualVal = Arith_Instr::M_StrToInt(l_valStr);
					*l_planetPtr /= l_actualVal;
				}
			};
			struct A_Mod : public A_Arith {
				void M_Exe(std::string p_inps[]) override {
					std::string l_planetDest = p_inps[0];
					std::string l_valStr = p_inps[1];
					int* l_planetPtr = rs::Regs::M_Shared().m_strPlanetMap[p_inps[0]]->m_regPtr;
					int l_actualVal;
					if(G_IsPlanet(l_valStr))
						l_actualVal = *rs::Regs::M_Shared().m_strPlanetMap[l_valStr]->m_regPtr;
					else l_actualVal = Arith_Instr::M_StrToInt(l_valStr);
					*l_planetPtr %= l_actualVal;
				}
			};
		private:
			static std::unordered_map<std::string,Arith_Instr::A_Arith*> m_mapInstr;
			std::string m_planetDest;
			std::string m_valStr;
			std::string m_arithStr;
		};
		std::unordered_map<std::string,Arith_Instr::A_Arith*> Arith_Instr::m_mapInstr;
	}
}

#endif