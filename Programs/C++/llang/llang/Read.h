#ifndef _READ
#define _READ

#include "Misc.h"
#include "IncludeRSV.h"
#include "CLine.h"

namespace CLine {
	class LineOfCode_Read : public LineOfCode {
	public:
		explicit LineOfCode_Read(const std::string& p_lineStr)
			: m_lineStr(p_lineStr)
		{
			m_essenFunc[0] = &LineOfCode_Read::M_GetDirStr;
			m_essenFunc[1] = &LineOfCode_Read::M_GetRSVStr;
			m_essenFunc[2] = &LineOfCode_Read::M_GetTypeOfRSV;

			m_readFunc[0] = &LineOfCode_Read::M_ReadSzet;
			m_readFunc[1] = &LineOfCode_Read::M_ReadChar;
			m_readFunc[2] = &LineOfCode_Read::M_ReadBool;
			m_readFunc[3] = &LineOfCode_Read::M_ReadStr;
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
	private:
		void M_ReadSzet(const std::string& p_cont) const {
			RSV_Const<size_t> l_constSzet(p_cont,type_int);
			VarHT::M_Shared().m_hTableOfSzet.M_FindVariable(m_RSVStr)->M_Val() = l_constSzet.M_GetValueOfRSV();
		}
		void M_ReadChar(const std::string& p_cont) const {
			RSV_Const<char> l_constChar(p_cont,type_char);
			VarHT::M_Shared().m_hTableOfChar.M_FindVariable(m_RSVStr)->M_Val() = l_constChar.M_GetValueOfRSV();
		}
		void M_ReadBool(const std::string& p_cont) const {
			RSV_Const<bool> l_constBool(p_cont,type_bool);
			VarHT::M_Shared().m_hTableOfBool.M_FindVariable(m_RSVStr)->M_Val() = l_constBool.M_GetValueOfRSV();
		}
		void M_ReadStr(const std::string& p_cont) const {
			RSV_String l_constStr(p_cont,false);
			VarHT::M_Shared().m_hTableOfStr.M_FindVariable(m_RSVStr)->M_Val() = l_constStr.M_GetValue();
		}
	public:
		void M_Translate(void) override {
			for(func_ptr l_essenFuncIter : m_essenFunc)
				(*this.*l_essenFuncIter)();
			m_fileSrc.open(m_dirStr);
			std::getline(m_fileSrc,m_contOfFile);
			for(size_t l_typeIter = 0; l_typeIter < 4; l_typeIter++)
				if(l_typeIter == m_typeOfRSV)
					(*this.*m_readFunc[l_typeIter])(m_contOfFile);
			m_fileSrc.close();
		}
	private:
		typedef void(LineOfCode_Read::*func_ptr)(void);
		typedef void(LineOfCode_Read::*func_ptrk)(const std::string&) const;

		func_ptr m_essenFunc[3];
		func_ptrk m_readFunc[4];

		type m_typeOfRSV;
		std::string m_lineStr;
		std::string m_contOfFile;
		std::string m_RSVStr;
		std::string m_dirStr;
		std::fstream m_fileSrc;
	};
}

#endif