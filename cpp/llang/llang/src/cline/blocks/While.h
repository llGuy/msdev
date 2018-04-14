#ifndef _WHILE
#define _WHILE

#include "../../misc/Misc.h"
#include "../base/CLine.h"
#include "misc/ScopeVar.h"
#include "misc/Condition.h"

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
			size_t l_indexCondEnd = m_whileLine.length();
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
			m_condObj.M_Init();
			while(m_condObj.M_Compare()) {
				for(size_t l_vecLineIter = 0; l_vecLineIter < m_vecLine.m_size; l_vecLineIter++) {
					m_vecLine[l_vecLineIter]->M_Translate();
					if(m_vecLine[l_vecLineIter]->M_IsVariableCreator()) {
						ScopeVar l_scpVar;
						l_scpVar.M_Update(m_vecLine[l_vecLineIter]);
						l_vecScpeVar.M_PushBack(l_scpVar);
						l_quantScpVar++;
					}
					m_condObj.M_Update(m_condStr);
					for(size_t l_iterScpVarArr = 0; l_iterScpVarArr < l_vecScpeVar.m_size; l_iterScpVarArr++)
						l_vecScpeVar[l_iterScpVarArr].M_Delete();
				}
			}
		}
		Vector<LineOfCode*>* M_GetBodyLineObj(void) override { return &m_vecLine; };
		Vector<std::string>* M_GetBodyStringLines(void) override { return &m_vecLineStr; };
	private:
		Vector<std::string> m_vecLineStr;
		Vector<LineOfCode*> m_vecLine;
		std::string m_whileLine;
		std::string m_condStr;
		Condition m_condObj;
	};
}

#endif