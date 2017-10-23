#ifndef _CLINE
#define _CLINE

#include "Vector.h"
#include "CNSTMacros.h" 
#include "VarHTables.h"

namespace CLine {
	//main class responsible
	//for all the possible types of instructions
	//that llang can execute
	class LineOfCode {
	public:
		explicit LineOfCode(void)
		{
		}
		//Destructor
		virtual ~LineOfCode(void)
		{
		}
	public:
		//virtual methods of LineOfCode
		
		//executes ("translates") the instructions written
		virtual void M_Translate(void) = 0;

		//for if statements when dealing with elifs and elses
		//so that llang knows which one is true
		//and when to stop the chain of ifs
		virtual const bool M_IsStatementTrue(void) { return false; };		//only for if statements

		//to know whether the line depends on other lines
		//such as a for loop or an if statement
		virtual const bool M_IsDependentOfBody(void) { return false; };

		//check if the instruction appends a variable into a HTable
		virtual const bool M_IsVariableCreator(void) { return false; };

		//returns a vector of the LineOfCode* of a block of code 
		//e.g. for loop
		virtual Vector<LineOfCode*>* M_GetBodyLineObj(void) { return nullptr; };

		//returns a vector of the std::string (lines) of a block of code
		virtual Vector<std::string>* M_GetBodyStringLines(void) { return nullptr; };
		
		// only for LineOfCode_Set
		//returns the "type" of the variable (e.g. string,int,bool...) as a string
		virtual const std::string M_GetTypeStr(void) { return _STR_NULL; };

		//returns a string of the name of a variable (e.g. "foo")
		virtual const std::string M_GetNameStr(void) { return _STR_NULL; };
	};
}
#endif