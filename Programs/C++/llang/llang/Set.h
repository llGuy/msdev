#ifndef _SET_CLINE
#define _SET_CLINE

#include "CLine.h"
#include "IncludeRSV.h"
#include "CNSTMacros.h"

namespace CLine {
	class LineOfCode_Set : public LineOfCode {
	public:
		explicit LineOfCode_Set(void)
		{
		}
		explicit LineOfCode_Set(const std::string& p_lineStr)
			: m_lineStr(p_lineStr)
		{
			m_getEssenComponents[2] = &LineOfCode_Set::M_GetRSV;
			m_getEssenComponents[1] = &LineOfCode_Set::M_GetName;
			m_getEssenComponents[0] = &LineOfCode_Set::M_GetStrType;

			m_possibleFunctionsTypeBase[0] = &LineOfCode_Set::M_IntFunction;
			m_possibleFunctionsTypeBase[1] = &LineOfCode_Set::M_CharFunction;
			m_possibleFunctionsTypeBase[2] = &LineOfCode_Set::M_BoolFunction;
			m_possibleFunctionsTypeBase[3] = &LineOfCode_Set::M_StringFunction;
		}
		~LineOfCode_Set(void)
		{
		}
	private:
		//essential functions
		//to get the components of the line
		inline void M_GetStrType(void) {
			size_t l_lineIter = 4;
			m_typeStr = ::G_BuildString(' ',l_lineIter,m_lineStr);
		}
		inline void M_GetName(void) {
			size_t l_lineIter = 5 + m_typeStr.length();
			m_nameStr = ::G_BuildString(' ',l_lineIter,m_lineStr);
		}
		inline void M_GetRSV(void) {
			size_t l_lineIter = 5 + m_typeStr.length() + m_nameStr.length() + 3;
			m_RSVStr = ::G_BuildString(';',l_lineIter,m_lineStr);
		}
		template<typename T>
		inline T M_CreateVariable(type p_typeSzet) {
			RSV_Variable<T> l_variable(m_RSVStr,p_typeSzet);
			return l_variable.M_GetValOfVar();
		}
		template<typename T>
		inline T M_CreateConstant(type p_typeSzet) {
			RSV_Const<T> l_constant(m_RSVStr,p_typeSzet);
			return l_constant.M_GetValueOfRSV();
		}
	private:
		void M_IntFunction(void) {
			//checks first if there is more than
			//one space
			if(::G_CalculateQuantOfWords(m_RSVStr) - 1 > 0) {
				RSV_Operation l_operRSV(m_RSVStr);
				size_t l_resOfOper = l_operRSV.M_GetValueOfOperation();
				VarHT::M_Shared().m_hTableOfSzet.M_AppendVar(l_resOfOper,m_nameStr);
			}
			else if(::G_CheckForVar(m_RSVStr)) {
				size_t l_valueOfVar = M_CreateVariable<size_t>(type_int);
				VarHT::M_Shared().m_hTableOfSzet.M_AppendVar(l_valueOfVar,m_nameStr);
			}
			else {
				size_t l_valueOfConstant = M_CreateConstant<size_t>(type_int);
				VarHT::M_Shared().m_hTableOfSzet.M_AppendVar(l_valueOfConstant,m_nameStr);
			}
		}
		void M_CharFunction(void) {
			if(::G_CheckForVar(m_RSVStr)) {
				char l_valueOfVariable = M_CreateVariable<char>(type_char);
				VarHT::M_Shared().m_hTableOfChar.M_AppendVar(l_valueOfVariable,m_nameStr);
			}
			else {
				char l_valueOfConstant = M_CreateConstant<char>(type_char);
				VarHT::M_Shared().m_hTableOfChar.M_AppendVar(l_valueOfConstant,m_nameStr);
			}
		}
		void M_BoolFunction(void) {
			if(::G_CheckForVar(m_RSVStr)) {
				bool l_valueOfVariable = M_CreateVariable<bool>(type_bool);
				VarHT::M_Shared().m_hTableOfBool.M_AppendVar(l_valueOfVariable,m_nameStr);
			}
			else {
				bool l_valueOfConstant = M_CreateConstant<bool>(type_bool);
				VarHT::M_Shared().m_hTableOfBool.M_AppendVar(l_valueOfConstant,m_nameStr);
			}
		}
		void M_StringFunction(void) {
			RSV_String l_strRSV(m_RSVStr,::G_CheckForVar(m_RSVStr));
			std::string l_valueOfRSV = l_strRSV.M_GetValue();
			VarHT::M_Shared().m_hTableOfStr.M_AppendVar(l_valueOfRSV,m_nameStr);
		}
	private:
		std::string m_RSVStr;
		const std::string m_POSSIBLE_TYPES[4] = {
			"int",
			"char",
			"bool",
			"string"
		};
		typedef void(LineOfCode_Set::*func_ptr)(void);
		func_ptr m_getEssenComponents[3];
		func_ptr m_possibleFunctionsTypeBase[4];
	public:
		//to be set as public for ScopeVar to read
		std::string m_lineStr;
		std::string m_typeStr;
		std::string m_nameStr;
	public:
		bool M_IsVariableCreator(void) override { return true; };
		void M_Translate(void) override {
			for(func_ptr l_funcEssentIter : m_getEssenComponents)
				(*this.*l_funcEssentIter)();
			for(size_t l_possTypesIter = 0; l_possTypesIter < 4; l_possTypesIter++) {
				if(m_POSSIBLE_TYPES[l_possTypesIter] == m_typeStr)
					(*this.*m_possibleFunctionsTypeBase[l_possTypesIter])();
			}
		}
		std::string M_GetTypeStr(void) override { return m_typeStr; };
		std::string M_GetNameStr(void) override { return m_nameStr; };
	};
}
#endif
