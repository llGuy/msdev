#ifndef _PRINT
#define _PRINT

#include "../../misc/Misc.h"
#include "../base/CLine.h"
#include "../../rsv/IncludeRSV.h"

namespace CLine {
	class LineOfCode_Print : public LineOfCode {
	public:
		explicit LineOfCode_Print(const std::string& p_lineStr,bool p_isLn = false)
			: m_lineStr(p_lineStr),m_isLn(p_isLn)
		{
			m_possPrintFunc[0] = &LineOfCode_Print::M_PrintSzet;
			m_possPrintFunc[1] = &LineOfCode_Print::M_PrintChar;
			m_possPrintFunc[2] = &LineOfCode_Print::M_PrintBool;
			m_possPrintFunc[3] = &LineOfCode_Print::M_PrintStr;
		}
	private:
		void M_GetRSVStr(void) {
			size_t l_lineStrIter = m_isLn ? 8 : 6;
			m_RSVStr = ::G_BuildString(';',l_lineStrIter,m_lineStr);
		}
		void M_GetTypeOfRSV(void) { 
			m_typeOfRSV = ::G_FetchTypeOfVar(m_RSVStr); 
			if(m_typeOfRSV == type_default)
				m_typeOfRSV = ::G_FetchTypeOfConst(m_RSVStr);
			if(m_typeOfRSV == type_default && ::G_CalculateQuantOfWords(m_RSVStr) - 1 > 0)
				m_typeOfRSV = type_int;
		};
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
		void M_PrintSzet(void) const {
			if(::G_CalculateQuantOfWords(m_RSVStr) - 1 > 0) {
				RSV_Operation l_operToPrint(m_RSVStr);
				size_t l_valOfOper = l_operToPrint.M_GetValueOfOperation();
				std::cout << l_valOfOper;
			}
			else if(::G_CheckForVar(m_RSVStr)) {
				size_t l_valOfVar = M_CreateVariable<size_t>(m_typeOfRSV);
				std::cout << l_valOfVar;
			}
			else {
				size_t l_valOfConst = M_CreateConstant<size_t>(m_typeOfRSV);
				std::cout << l_valOfConst;
			}
		}
		void M_PrintChar(void) const {
			if(::G_CheckForVar(m_RSVStr)) {
				char l_valOfVar = M_CreateVariable<char>(m_typeOfRSV);
				std::cout << l_valOfVar;
			}
			else {
				char l_valOfConst = M_CreateConstant<char>(m_typeOfRSV);
				std::cout << l_valOfConst;
			}
		}
		void M_PrintBool(void) const {
			if(::G_CheckForVar(m_RSVStr)) {
				bool l_valOfVar = M_CreateVariable<bool>(m_typeOfRSV);
				std::cout << l_valOfVar ? "true" : "false";
			}
			else {
				bool l_valOfConst = M_CreateConstant<bool>(m_typeOfRSV);
				std::cout << l_valOfConst ? "true" : "false";
			}
		}
		void M_PrintStr(void) const {
			RSV_String l_strRSV(m_RSVStr,::G_CheckForVar(m_RSVStr) ? true : false);
			std::cout << l_strRSV.M_GetValue();
 		}
	public:
		void M_Translate(void) override {
			M_GetRSVStr();
			M_GetTypeOfRSV();
			for(size_t l_funcIter = 0; l_funcIter < 4; l_funcIter++) {
				if((size_t)m_typeOfRSV == l_funcIter) 
					(*this.*m_possPrintFunc[l_funcIter])();
			}
			std::string l_endTermination = m_isLn ? "\n" : "";
			std::cout << l_endTermination;
		}
	private:
		typedef void(LineOfCode_Print::*func_ptrk)(void) const;
		func_ptrk m_possPrintFunc[4];
		std::string m_lineStr;
		std::string m_RSVStr;
		type m_typeOfRSV;
		bool m_isLn;
	};
}
#endif