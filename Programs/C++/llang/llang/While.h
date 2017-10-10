#ifndef _WHILE
#define _WHILE

#include "Misc.h"
#include "CLine.h"
#include "ScopeVar.h"
#include "Condition.h"

namespace CLine {
	class LineOfCode_While : public LineOfCode {
	public:
		explicit LineOfCode_While(Vector<std::string>& p_vecLineStr)
		{
			m_whileLine = p_vecLineStr[0];
			for(size_t l_vecIter = 1; l_vecIter < p_vecLineStr.m_size; l_vecIter++)
				m_vecLineStr.M_PushBack(p_vecLineStr[l_vecIter]);
		}
	private:
		void M_GetCondStr(void) {
			size_t l_indexCondStrt = 6;
			size_t l_indexCondEnd = m_whileLine.length() - 1;
			bool l_foundEnd = false;
			while(l_indexCondStrt < l_indexCondEnd) {
				m_condStr += m_whileLine[l_indexCondStrt];
				l_indexCondStrt++;
			}
		}
	public:
		void M_Translate(void) override {
			M_GetCondStr();
			m_condObj.m_condStr = this->m_condStr;
			Vector<ScopeVar> l_vecScpeVar;
			size_t l_quantScpVar = 0;
		}
	private:
		Vector<std::string> m_vecLineStr;
		Vector<LineOfCode*> m_vecLine;
		std::string m_whileLine;
		std::string m_condStr;
		Condition m_condObj;
	};
}

#endif