#ifndef _IF
#define _IF

#include "../base/CLine.h"

namespace CLine {
	class LineOfCode_If : public LineOfCode {
	public:
		explicit LineOfCode_If(const Vector<std::string> &p_vecOfLineStr,const bool p_isElif = false)
		{
			m_isElif = p_isElif;
			m_ifLine = p_vecOfLineStr[0];
			for(size_t l_vecIter = 1; l_vecIter < p_vecOfLineStr.m_size; l_vecIter++)
				m_vecOfLineStr.M_PushBack(p_vecOfLineStr[l_vecIter]);
			M_GetCondStr();
			m_condObj.m_condStr = this->m_condStr;
		}
	private:
		void M_GetCondStr(void) {
			size_t l_strIter = m_isElif ? 5 : 3;
			while(m_ifLine[l_strIter] != '\0') {
				m_condStr += m_ifLine[l_strIter];
				l_strIter++;
			}
		}
	public:
		void M_Translate(void) override {
			const std::string l_condIf = m_condObj.m_condStr;
			m_condObj.M_Init();
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
		Vector<LineOfCode*>* M_GetBodyLineObj(void) override { return &m_vecOfLine; };
		Vector<std::string>* M_GetBodyStringLines(void) override { return &m_vecOfLineStr; };
		const bool M_IsStatementTrue(void) override { return m_isCondTrue; };
	private:
		Vector<std::string> m_vecOfLineStr;
		Vector<LineOfCode*> m_vecOfLine;
		bool m_isCondTrue = false;
		bool m_isElif = false;
		std::string m_condStr;
		std::string m_ifLine;
		Condition m_condObj;
	};
}

#endif