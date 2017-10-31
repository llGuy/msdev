#ifndef _FUNC
#define _FUNC

#include "../../base/CLine.h"
#include "../../../misc/Misc.h"
namespace CLine {
	namespace func {
		class Func {
		public:
			explicit Func(void)
			{
			}
			explicit Func(const Vector<LineOfCode*>& p_vecLineObj,
				const Vector<std::string>& p_vecSetLineStr,
				type p_returnType,std::string p_funcName)
				: m_vecLineObj(p_vecLineObj),
				m_vecSetLineStr(p_vecSetLineStr),m_returnType(p_returnType),
				m_funcName(p_funcName)
			{
			}
		public:
			void M_ExecuteInstructions(void) {
				Vector<ScopeVar> l_vecScpVar;
				for(size_t l_vecLineIter = 0; l_vecLineIter < m_vecLineObj.m_size; l_vecLineIter++) {
					if(m_vecLineObj[l_vecLineIter]->M_IsVariableCreator()) {
						ScopeVar l_scpVar;
						l_scpVar.M_Update(m_vecLineObj[l_vecLineIter]);
						l_vecScpVar.M_PushBack(l_scpVar);
					}
					if(m_vecLineObj[l_vecLineIter]->M_IsRetState()) break;
					m_vecLineObj[l_vecLineIter]->M_Translate();
				}
				for(size_t l_vecScpVarIter = 0; l_vecScpVarIter < l_vecScpVar.m_size; l_vecScpVarIter++)
					l_vecScpVar[l_vecScpVarIter].M_Delete();
			}
		public:
			Vector<LineOfCode*>& M_VecLineObj(void) { return m_vecLineObj; };
			Vector<std::string>& M_VecSetLineStr(void) { return m_vecSetLineStr; };
			type& M_RetType(void) { return m_returnType; };
			std::string& M_FuncName(void) { return m_funcName; };
		private:
			//LineOfCode*s to execute whilst being called
			Vector<LineOfCode*> m_vecLineObj;
			//LineOfCode_Sets in strings which will instantiate the parameters
			//later when the function gets called
			Vector<std::string> m_vecSetLineStr;
			type m_returnType;
			std::string m_funcName;
		};
	}
}

#endif