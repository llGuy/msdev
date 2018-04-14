#ifndef _CALL
#define _CALL

#include "func-hash/FuncHT.h"

namespace CLine {
	namespace func {
		class LineOfCode_Call : public LineOfCode {
		public:
			explicit LineOfCode_Call(const std::string& p_callLine)
				: m_callLine(p_callLine)
			{
			}
		private:
			void M_GetFuncName(void) {
				size_t l_indName = 6;
				m_funcName = ::G_BuildString('{',l_indName,m_callLine);
			}
			void M_GetParams(void) {
				size_t l_indParams = 6 + m_funcName.length() + 1;
				std::string l_temp;
				while(m_callLine[l_indParams] != '}') {
					l_temp += m_callLine[l_indParams];
					if(m_callLine[l_indParams] == ';')
						m_params.M_PushBack(l_temp); 
					else continue;
				}
			}
		public:
			void M_Translate(void) {
				M_GetFuncName();
				M_GetParams();
			}
		private:
			std::string m_callLine;
			std::string m_funcName;
			Vector<std::string> m_params;
		};
	}
}

#endif