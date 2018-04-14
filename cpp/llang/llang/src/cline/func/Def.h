#ifndef _DEF
#define _DEF

#include "../base/CLine.h"
#include "../IncludeCLine.h"
#include "func-hash/FuncHT.h"

namespace CLine {
	namespace func {
		class LineOfCode_Def : public LineOfCode {
		public:
			explicit LineOfCode_Def(const Vector<std::string>& p_vecLineStr)
				: m_quantSetLine(_NULL),m_retType(type_default)
			{
				m_defLine = p_vecLineStr[0];
				for(size_t l_vecIter = 1; l_vecIter < p_vecLineStr.m_size; l_vecIter)
					m_vecLineStr[l_vecIter] = p_vecLineStr[l_vecIter];
			}
		private:
			void M_GetFuncName(void) {
				size_t l_indexOfName = 5;		//def :blah		<- 'b' at index 5
				m_funcName = ::G_BuildString('{',l_indexOfName,m_defLine);
			}
			const std::string M_GetContBetSquirlBrack(void) const {
				size_t l_indexOfConts = 5 + m_funcName.length() + 1;
				std::string l_conts = ::G_BuildString('}',l_indexOfConts,m_defLine);
				return l_conts;
			}
			void M_GetSetLineStrs(void) {
				std::string l_conts = M_GetContBetSquirlBrack();
				size_t l_contIter = 0;
				std::string l_tempSetLineStr;
				while(l_contIter < l_conts.length()) {
					l_tempSetLineStr += l_conts[l_contIter];
					if(l_conts[l_contIter] == ';')
						m_vecSetLineStr.M_PushBack(l_tempSetLineStr);
					else continue;
				}
			}
			std::string M_GetReturnTypeStr(void) {
				size_t l_indexRetType = 5 + m_funcName.length() + 1 + M_GetContBetSquirlBrack().length() + 4;
				std::string l_retTypeStr;
				while(l_indexRetType != '\0' || l_indexRetType != ' ') {
					l_retTypeStr += m_defLine[l_indexRetType];
					l_indexRetType++;
				}
				return l_retTypeStr;
			}
			void M_GetReturnType(void) {
				std::string l_typeStrArr[] ={
					"int",
					"char",
					"bool",
					"string",
					"void"
				};
				type l_type[] ={
					type_int,
					type_char,
					type_bool,
					type_str,
					type_default
				};
				std::string l_typeStr = M_GetReturnTypeStr();
				for(size_t l_typeArrIter = 0; l_typeArrIter < 5; l_typeArrIter++) {
					if(l_typeStrArr[l_typeArrIter] == l_typeStr) {
						m_retType = l_type[l_typeArrIter];
						return;
					}
				}
			}
		public:
			void M_Translate(void) override {
				M_GetFuncName();
				M_GetSetLineStrs();
				M_GetReturnType();
				m_func.M_VecLineObj() = m_vecLineObj;
				m_func.M_VecSetLineStr() = m_vecSetLineStr;
				m_func.M_RetType() = m_retType;
				m_func.M_FuncName() = m_funcName;
				Func_HashT::M_Shared().m_funcHashT.M_AppendVar(m_func,m_funcName);
			}
			Vector<LineOfCode*>* M_GetBodyLineObj(void) override { return &m_vecLineObj; };
			Vector<std::string>* M_GetBodyStringLines(void) override { return &m_vecLineStr; };
		private:
			type m_retType;
			size_t m_quantSetLine;
			Vector<std::string> m_vecLineStr;
			Vector<LineOfCode*> m_vecLineObj;
			Vector<std::string> m_vecSetLineStr;
			std::string m_defLine;
			std::string m_funcName;
			Func m_func;
		};
	}
}

#endif