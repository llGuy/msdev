#ifndef _IF
#define _IF

#include "CLine.h"

namespace CLine {
	class LineOfCode_If : public LineOfCode {
	public:
		explicit LineOfCode_If(const Vector<std::string> &p_vecOfLineStr)
		{
			m_condStr = p_vecOfLineStr[0];
			for(size_t l_vecIter = 1; l_vecIter < p_vecOfLineStr.m_size; l_vecIter)
				m_vecOfLineStr.M_PushBack(m_vecOfLineStr[l_vecIter]);
			M_GetCondStr();
			m_condObj.m_condStr = this->m_condStr;
		}
	private:
		void M_GetCondStr(void) {
			size_t l_strIter = 3;
			std::string l_newStr;
			while(m_condStr[l_strIter] != '\0') {
				l_newStr += m_condStr[l_strIter];
				l_strIter++;
			}
		}
	public:
		void M_Translate(void) override {
			const std::string l_condIf = m_condObj.m_condStr;
			m_isCondTrue = m_condObj.M_Compare();
			if(m_isCondTrue) {
				Vector<ScopeVar> l_vecScpeVar;
				for(size_t l_vecIter = 0; l_vecIter < m_vecOfLine.m_size; l_vecIter++) {
					if(m_vecOfLine[l_vecIter]->M_IsVariableCreator()) {
						ScopeVar l_scpVar;
						l_scpVar.M_Update(m_vecOfLine[l_vecIter]);
						l_vecScpeVar.M_PushBack(l_scpVar);
					}
					m_vecOfLine[l_vecIter]->M_Translate();
				}
				for(size_t l_scpVarVecIter = 0; l_scpVarVecIter < l_vecScpeVar.m_size; l_scpVarVecIter++)
					l_vecScpeVar[l_scpVarVecIter].M_Delete();
				m_condObj.M_Update(m_condStr);
			}
			else m_condObj.M_Update(m_condStr);
		}
	private:
		Vector<std::string> m_vecOfLineStr;
		Vector<LineOfCode*> m_vecOfLine;
		bool m_isCondTrue = false;
		std::string m_condStr;
		Condition m_condObj;
	};
}

#endif