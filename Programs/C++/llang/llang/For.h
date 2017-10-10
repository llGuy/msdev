#ifndef _FOR
#define _FOR

#include "Misc.h"
#include "CLine.h"
#include "ScopeVar.h"
#include "Condition.h"

namespace CLine {
	class LineOfCode_For : public LineOfCode {
	public:
		explicit LineOfCode_For(Vector<std::string>& p_vecLineStr) 
		{
			m_forLine = p_vecLineStr[0];
			for(size_t l_vecIter = 1; l_vecIter < p_vecLineStr.m_size; l_vecIter++)
				m_vecLineStr.M_PushBack(p_vecLineStr[l_vecIter]);
		}
	private:
		void M_GetNameOfIter(void) {
			size_t l_strIndex = 5;
			while(m_forLine[l_strIndex] != ']') {
				m_nameIterStr += m_forLine[l_strIndex];
				l_strIndex++;
			}
		}
		void M_GetCondStr(void) {
			size_t l_indexCondStrt = 4;
			size_t l_indexCondEnd = m_forLine.length() - 1;
			bool l_foundEnd = false;
			while(!l_foundEnd) {
				if(m_forLine[l_indexCondEnd] != '+'&&m_forLine[l_indexCondEnd] != '-')
					l_indexCondEnd--;
				else l_foundEnd = true;
			}
			while(l_indexCondStrt < l_indexCondEnd) {
				m_condStr += m_forLine[l_indexCondStrt];
				l_indexCondStrt++;
			}
		}
		void M_GetOperOfInc(void) { m_iterOper = m_forLine[m_forLine.length() - 1]; };
		void M_Incr(void) {
			if(m_iterOper == '+') VarHT::M_Shared().m_hTableOfSzet.M_FindVariable(m_nameIterStr)->m_value += 1;
			if(m_iterOper == '-') VarHT::M_Shared().m_hTableOfSzet.M_FindVariable(m_nameIterStr)->m_value -= 1;
		}
	public:
		void M_Translate(void) override {
			M_GetNameOfIter();
			M_GetCondStr();
			M_GetOperOfInc();
			m_condObj.m_condStr = this->m_condStr; //put this to avoid confusion
			Vector<ScopeVar> l_vecScpeVar;
			size_t l_quantScpVar = 0;
			size_t l_loopIndex = 0;
			m_condObj.M_Init();
			while(m_condObj.M_Compare()) {
				l_quantScpVar++;
				for(size_t l_vecLinesIter = 0; l_vecLinesIter < m_vecLine.m_size; l_vecLinesIter++) {
					m_vecLine[l_vecLinesIter]->M_Translate();
					if(m_vecLine[l_vecLinesIter]->M_IsVariableCreator()) {
						ScopeVar l_scpVar;
						l_scpVar.M_Update(m_vecLine[l_vecLinesIter]);
						l_vecScpeVar.M_PushBack(l_scpVar);
						l_quantScpVar++;
					}
				}
				l_loopIndex++;
				M_Incr();
				m_condObj.M_Update(m_condStr);
				for(size_t l_iterScpVarArr = 0; l_iterScpVarArr < l_vecScpeVar.m_size; l_iterScpVarArr++)
					l_vecScpeVar[l_iterScpVarArr].M_Delete();
			}
		}
		Vector<LineOfCode*>* M_GetBodyLineObj(void) override { return &m_vecLine; };
		Vector<std::string>* M_GetBodyStringLines(void) override { return &m_vecLineStr; };
	private:
		Vector<std::string> m_vecLineStr;
		Vector<LineOfCode*> m_vecLine;
		std::string m_forLine;
		std::string m_nameIterStr;
		std::string m_condStr;
		Condition m_condObj;
		char m_iterOper;
	};
}

#endif