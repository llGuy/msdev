#ifndef _SAVE
#define _SAVE

#include "Misc.h"
#include "IncludeRSV.h"
#include "CLine.h"

namespace CLine {
	class LineOfCode_Save : public LineOfCode {
	public:
		explicit LineOfCode_Save(const std::string& p_lineStr)
			: m_lineStr(p_lineStr)
		{
			m_saveFileFunc[0] = &LineOfCode_Save::M_SaveSzet;
			m_saveFileFunc[1] = &LineOfCode_Save::M_SaveChar;
			m_saveFileFunc[2] = &LineOfCode_Save::M_SaveBool;
			m_saveFileFunc[3] = &LineOfCode_Save::M_SaveStr;
		}
	private:
		void M_GetDirStr(void) {
			size_t l_indexDirStrt = 6;
			m_dirStr = ::G_BuildString('\"',l_indexDirStrt,m_lineStr);
		}
		void M_GetRSVStr(void) {
			size_t l_indexRSVStrt = 6 + m_dirStr.length() + 2;
			m_RSVStr = ::G_BuildString(';',l_indexRSVStrt,m_lineStr);
		}
		void M_GetTypeOfRSV(void) {
			m_typeOfRSV = ::G_FetchTypeOfVar(m_RSVStr);
			if(m_typeOfRSV == type_default)
				m_typeOfRSV = ::G_FetchTypeOfConst(m_RSVStr);
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
		void M_SaveSzet(void) {
			if(::G_CalculateQuantOfWords(m_RSVStr) - 1 > 0) {
				RSV_Operation l_oper(m_RSVStr);
				size_t l_valOper = l_oper.M_GetValueOfOperation();
				m_fileDest << l_valOper;
				return;
			}
			else if(::G_CheckForVar(m_RSVStr)) {
				size_t l_valVar = M_CreateVariable<size_t>(type_int);
				m_fileDest << l_valVar;
				return;
			}
			else {
				size_t l_valConst = M_CreateConstant<size_t>(type_int);
				m_fileDest << l_valConst;
				return;
			}
		}
		void M_SaveChar(void) {
			if(::G_CheckForVar(m_RSVStr)) {
				char l_valVar = M_CreateVariable<char>(type_char);
				m_fileDest << '\'' <<l_valVar << '\'';
				return;
			}
			else {
				char l_valConst = M_CreateConstant<char>(type_char);
				m_fileDest << '\'' << l_valConst << '\'';
				return;
			}
		}
		void M_SaveBool(void) {
			if(::G_CheckForVar(m_RSVStr)) {
				bool l_valVar = M_CreateVariable<bool>(type_bool);
				std::string l_strBool = l_valVar ? "true" : "false";
				m_fileDest << l_strBool;
				return;
			}
			else {
				bool l_valConst = M_CreateConstant<bool>(type_bool);
				std::string l_strBool = l_valConst ? "true" : "false";
				m_fileDest << l_strBool;
				return;
			}
		}
		void M_SaveStr(void) {
			RSV_String l_strRSVObj(m_RSVStr,::G_CheckForVar(m_RSVStr));
			std::string l_valStr = l_strRSVObj.M_GetValue();
			m_fileDest << '\"' << l_valStr << '\"';
		}
	public:
		void M_Translate(void) override {
			M_GetDirStr();
			M_GetRSVStr();
			M_GetTypeOfRSV();

			m_fileDest.open(m_dirStr);

			for(size_t l_funcIter = 0; l_funcIter < 4; l_funcIter++) {
				if(l_funcIter == (size_t)m_typeOfRSV) {
					(*this.*m_saveFileFunc[l_funcIter])();
					return;
				}
			} 
			m_fileDest.close();
		}
	private:
		typedef void(LineOfCode_Save::*func_ptr)(void);
		func_ptr m_saveFileFunc[4];	//type specific
		std::string m_lineStr;
		std::string m_RSVStr;
		std::string m_dirStr;
		type m_typeOfRSV;
		std::fstream m_fileDest;
	};
	
}

#endif