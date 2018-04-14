#ifndef _ELSE
#define _ELSE

#include "../base/CLine.h"

namespace CLine {
	class LineOfCode_Else : public LineOfCode {
	public:
		explicit LineOfCode_Else(const Vector<std::string> &p_vecLineStr) {
			for(size_t l_vecIter = 1; l_vecIter < p_vecLineStr.m_size; l_vecIter++)
				m_vecLineStr.M_PushBack(p_vecLineStr[l_vecIter]);
		}
	public:
		void M_Translate(void) override {
			Vector<ScopeVar> l_vecScpVar;
			for(size_t l_vecLineIter = 0; l_vecLineIter < m_vecLine.m_size; l_vecLineIter++) {
				if(m_vecLine[l_vecLineIter]->M_IsVariableCreator()) {
					ScopeVar l_scpVar;
					l_scpVar.M_Update(m_vecLine[l_vecLineIter]);
					l_vecScpVar.M_PushBack(l_scpVar);
				}
				m_vecLine[l_vecLineIter]->M_Translate();
			}
			for(size_t l_vecScpVarIter = 0; l_vecScpVarIter < l_vecScpVar.m_size; l_vecScpVarIter++)
				l_vecScpVar[l_vecScpVarIter].M_Delete();
		}
		Vector<LineOfCode*>* M_GetBodyLineObj(void) override { return &m_vecLine; };
		Vector<std::string>* M_GetBodyStringLines(void) override { return &m_vecLineStr; };
	private:
		Vector<std::string> m_vecLineStr;
		Vector<LineOfCode*> m_vecLine;
	};
}
#endif