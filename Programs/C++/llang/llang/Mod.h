#ifndef _MOD
#define _MOD

#include "Misc.h"
#include "CLine.h"
#include "IncludeRSV.h"

namespace CLine {
	class LineOfCode_Mod : public LineOfCode {
	public:
		explicit LineOfCode_Mod(const std::string& p_lineStr)
			: m_lineStr(p_lineStr)
		{
			m_getEssenComponents[0] = &LineOfCode_Mod::M_GetName;
			m_getEssenComponents[1] = &LineOfCode_Mod::M_GetRSV;
			m_getEssenComponents[2] = &LineOfCode_Mod::M_GetTypeOfVarToMod;

			m_possibleFunctionsTypeBased[0] = &LineOfCode_Mod::M_FunctionSzet;
			m_possibleFunctionsTypeBased[1] = &LineOfCode_Mod::M_FunctionChar;
			m_possibleFunctionsTypeBased[2] = &LineOfCode_Mod::M_FunctionBool;
			m_possibleFunctionsTypeBased[3] = &LineOfCode_Mod::M_FunctionStr;
		}
		~LineOfCode_Mod(void)
		{
		}
	private:
		inline void M_GetName(void) {
			size_t l_lineIter = 4;
			m_nameStr = G_BuildString(' ',l_lineIter,m_lineStr);
		}
		inline void M_GetRSV(void) {
			size_t l_lineIter = 4 + m_nameStr.length() + 4;
			m_RSVStr = G_BuildString(';',l_lineIter,m_lineStr);
		}
		inline void M_GetTypeOfVarToMod(void) {
			m_typeVarToMod = ::G_FetchTypeOfVar(m_nameStr);
		}
		template<typename T>
		inline T M_CreateVariable(type p_typeSzet) const {
			RSV_Variable<T> l_variable(m_RSVStr,p_typeSzet);
			return l_variable.M_GetValOfVar();
		}
		template<typename T>
		inline T M_CreateConstant(type p_typeSzet) const {
			RSV_Const<T> l_constant(m_RSVStr,p_typeSzet);
			return l_constant.M_GetValueOfRSV();
		}
	private:
		void M_FunctionSzet(void) const {
			if(::G_CalculateQuantOfWords(m_RSVStr)) {
				RSV_Operation l_operation(m_RSVStr);
				size_t l_valueOfOperation = l_operation.M_GetValueOfOperation();
				VarHT::M_Shared().m_hTableOfSzet.M_FindVariable(m_nameStr)->M_Val() = l_valueOfOperation;
			}
			else if(::G_CheckForVar(m_RSVStr)) {
				size_t l_valueOfVar = M_CreateVariable<size_t>(type_int);
				VarHT::M_Shared().m_hTableOfSzet.M_FindVariable(m_nameStr)->M_Val() = l_valueOfVar;
			}
			else {
				size_t l_valueOfConst = M_CreateConstant<size_t>(type_int);
				VarHT::M_Shared().m_hTableOfSzet.M_FindVariable(m_nameStr)->M_Val() = l_valueOfConst;
			}
		}
		void M_FunctionChar(void) const {
			if(::G_CheckForVar(m_RSVStr)) {
				char l_valueOfVar = M_CreateVariable<char>(type_char);
				VarHT::M_Shared().m_hTableOfChar.M_FindVariable(m_nameStr)->M_Val() = l_valueOfVar;
			}
			else {
				char l_valueOfConstant = M_CreateConstant<char>(type_char);
				VarHT::M_Shared().m_hTableOfChar.M_FindVariable(m_nameStr)->M_Val() = l_valueOfConstant;
			}
		}
		void M_FunctionBool(void) const {
			if(::G_CheckForVar(m_RSVStr)) {
				bool l_valueOfVar = M_CreateVariable<bool>(type_bool);
				VarHT::M_Shared().m_hTableOfBool.M_FindVariable(m_nameStr)->M_Val() = l_valueOfVar;
			}
			else {
				bool l_valueOfConstant = M_CreateConstant<bool>(type_bool);
				VarHT::M_Shared().m_hTableOfBool.M_FindVariable(m_nameStr)->M_Val() = l_valueOfConstant;
			}
		}
		void M_FunctionStr(void) const {
			RSV_String l_strRSV(m_RSVStr,::G_CheckForVar(m_RSVStr));
			std::string l_valueOfRSV = l_strRSV.M_GetValue();
			VarHT::M_Shared().m_hTableOfStr.M_FindVariable(m_nameStr)->M_Val() = l_valueOfRSV;
		}
	private:
		typedef void(LineOfCode_Mod::*func_ptr)(void);
		typedef void(LineOfCode_Mod::*func_ptrk)(void) const;
		std::string m_lineStr;
		const type m_POSSIBLE_TYPES[5] = {
			type_int,
			type_char,
			type_bool,
			type_str,
			type_default
		};
		type m_typeVarToMod;
		std::string m_RSVStr;
		std::string m_nameStr;
		func_ptrk m_possibleFunctionsTypeBased[4];
		func_ptr m_getEssenComponents[3];
	public:
		void M_Translate(void) override {
			for(func_ptr l_funcPtrIter : m_getEssenComponents)
				(*this.*l_funcPtrIter)();
			for(size_t l_typeIter = 0; l_typeIter < 4; l_typeIter++) {
				if((size_t)m_typeVarToMod == l_typeIter)
					(*this.*m_possibleFunctionsTypeBased[l_typeIter])();
			}
		}
	};
}

#endif