#ifndef _IF_STATEMENT
#define _IF_STATEMENT

#include "../base/CLine.h"

namespace CLine {
	class LineOfCode_IfStatement : public LineOfCode {
	public:
		explicit LineOfCode_IfStatement(const Vector<LineOfCode*> p_vecIfElifElseLine)
			: m_vecIfElifElseLine(p_vecIfElifElseLine)
		{
		}
	public:
		void M_Translate(void) override {
			bool l_valueOfPreviousIf = false;
			size_t l_vecIter = 0;
			while(l_vecIter < m_vecIfElifElseLine.m_size) {
				if(!l_valueOfPreviousIf) {
					m_vecIfElifElseLine[l_vecIter]->M_Translate();
					l_valueOfPreviousIf = m_vecIfElifElseLine[l_vecIter]->M_IsStatementTrue();
				}
				else break;
				l_vecIter++;
			}
		}
		const bool M_IsDependentOfBody(void) override { return true; };
		Vector<LineOfCode*>* M_GetBodyLineObj(void) override { return &m_vecIfElifElseLine; };
	private:
		Vector<LineOfCode*> m_vecIfElifElseLine;
	};
}

#endif