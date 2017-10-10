#ifndef _CLINE
#define _CLINE

#include "Vector.h"
#include "CNSTMacros.h" 
#include "VarHTables.h"

namespace CLine {
	class LineOfCode {
	public:
		explicit LineOfCode(void)
		{
		}
		~LineOfCode(void)
		{
		}
	public:
		//virtual methods of LineOfCode
		virtual void M_Translate(void) = 0;
		virtual const bool M_IsStatementTrue(void) { return false; };		//only for if statements
		virtual const bool M_IsDependentOfBody(void) { return false; };
		virtual const bool M_IsVariableCreator(void) { return false; };
		virtual Vector<LineOfCode*>* M_GetBodyLineObj(void) { return nullptr; };
		virtual Vector<std::string>* M_GetBodyStringLines(void) { return nullptr; };
		// only for LineOfCode_Set
		virtual const std::string M_GetTypeStr(void) { return _STR_NULL; };
		virtual const std::string M_GetNameStr(void) { return _STR_NULL; };
	};
}
#endif