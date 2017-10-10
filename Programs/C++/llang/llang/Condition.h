#ifndef _CONDITION
#define _CONDITION

#include "Misc.h"
#include "IncludeRSV.h"

class Condition {
public: 
	explicit Condition(void) 
	{
	}
	explicit Condition(const std::string& p_condStr)
		: m_condStr(p_condStr)
	{
	}
private:
	void M_GetValOfFirstComp(void) { 
		m_RSVStr[0] = ::G_BuildString(']',1,m_condStr); }
	void M_GetValOfScndComp(void) { 
		m_RSVStr[1] = ::G_BuildString(']',1 + m_RSVStr[0].length() + 5,m_condStr); };
	void M_GetOperand(void) {
		char l_operandChr = m_condStr[1 + m_RSVStr[0].length() + 2];
		std::unordered_map<operand,char> l_operandMap;
		l_operandMap[equ] = '=';
		l_operandMap[grt] = '>';
		l_operandMap[less] = '<';
		l_operandMap[notequ] = '!';
		for(auto l_operMapIter = l_operandMap.begin(); l_operMapIter != l_operandMap.end(); ++l_operMapIter) {
			if(l_operMapIter->second == l_operandChr) {
				m_operOfCond = l_operMapIter->first;
				return;
			}
		}
	}
	void M_GetTypeOfCond(void) {
		for(size_t l_arrRSVIter = 0; l_arrRSVIter < 2; l_arrRSVIter++) {
			type l_tempType = ::G_FetchTypeOfConst(m_RSVStr[l_arrRSVIter]);
			if(l_tempType == type_default) {
				if(::G_CalculateQuantOfWords(m_RSVStr[l_arrRSVIter]) - 1 == 0) {
					m_isVar[l_arrRSVIter] = true;
					m_typeOfCond = ::G_FetchTypeOfVar(m_RSVStr[l_arrRSVIter]);
				}
				else {
					m_isVar[l_arrRSVIter] = false;
					m_typeOfCond = type_int;
				}
			}
			else {
				m_isVar[l_arrRSVIter] = false;
				switch(l_tempType) {
				case type_int:
					m_typeOfCond = type_int;
					return;
				case type_char:
					m_typeOfCond = type_char;
					return;
				case type_bool:
					m_typeOfCond = type_bool;
					return;
				case type_str:
					m_typeOfCond = type_str;
					return;
				}
			}
		}
	}
	template<typename T>
	const bool M_PerfOper(T p_comp1,T p_comp2) {
		auto l_equLam = [=](void)->bool {return p_comp1 == p_comp2; };
		auto l_grtLam = [=](void)->bool {return p_comp1 > p_comp2; };
		auto l_lessLam = [=](void)->bool {return p_comp1 < p_comp2; };
		auto l_notLam = [=](void)->bool {return p_comp1 != p_comp2; };
		std::unordered_map<operand,std::function<bool(void)>> l_mapOfCompareLam;
		l_mapOfCompareLam[equ] = l_equLam;
		l_mapOfCompareLam[grt] = l_grtLam;
		l_mapOfCompareLam[less] = l_lessLam;
		l_mapOfCompareLam[notequ] = l_notLam;
		for(auto l_mapIter = l_mapOfCompareLam.begin(); l_mapIter != l_mapOfCompareLam.end(); ++l_mapIter) {
			if(l_mapIter->first == m_operOfCond) {
				m_isCondTrue = l_mapIter->second();
				return m_isCondTrue;
			}
		}
		return false;
	}
	void M_CompSzet(void) {
		size_t l_bothVal[2];
		for(size_t l_arrIter = 0; l_arrIter < 2; l_arrIter++) {
			if(::G_CalculateQuantOfWords(m_RSVStr[l_arrIter]) - 1 > 0) {
				RSV_Operation l_oper(m_RSVStr[l_arrIter]);
				l_bothVal[l_arrIter] = l_oper.M_GetValueOfOperation();
			}
			else if(::G_CheckForVar(m_RSVStr[l_arrIter])) {
				RSV_Variable<size_t> l_varSzet(m_RSVStr[l_arrIter],type_int);
				l_bothVal[l_arrIter] = l_varSzet.M_GetValOfVar();
			}
			else {
				RSV_Const<size_t> l_constSzet(m_RSVStr[l_arrIter],type_int);
				l_bothVal[l_arrIter] = l_constSzet.M_GetValueOfRSV();
			}
		}
		M_PerfOper<size_t>(l_bothVal[0],l_bothVal[1]);
	}
	void M_CompChar(void) {
		char l_bothVal[2];
		for(size_t l_arrIter = 0; l_arrIter < 2; l_arrIter++) {
			if(::G_CheckForVar(m_RSVStr[l_arrIter])) {
				RSV_Variable<char> l_varChar(m_RSVStr[l_arrIter],type_char);
				l_bothVal[l_arrIter] = l_varChar.M_GetValOfVar();
			}
			else {
				RSV_Const<char> l_constChar(m_RSVStr[l_arrIter],type_char);
				l_bothVal[l_arrIter] = l_constChar.M_GetValueOfRSV();
			}
		}
		M_PerfOper<char>(l_bothVal[0],l_bothVal[1]);
	}
	void M_CompBool(void) {
		bool l_bothVal[2];
		for(size_t l_arrIter = 0; l_arrIter < 2; l_arrIter++) {
			if(::G_CheckForVar(m_RSVStr[l_arrIter])) {
				RSV_Variable<bool> l_varBool(m_RSVStr[l_arrIter],type_bool);
				l_bothVal[l_arrIter] = l_varBool.M_GetValOfVar();
			}
			else {
				RSV_Const<char> l_constBool(m_RSVStr[l_arrIter],type_bool);
				l_bothVal[l_arrIter] = l_constBool.M_GetValueOfRSV();
			}
		}
		M_PerfOper<bool>(l_bothVal[0],l_bothVal[1]);
	}
	void M_CompStr(void) {
		std::string l_bothVal[2];
		for(size_t l_arrIter = 0; l_arrIter < 2; l_arrIter++) {
			RSV_String l_strRSV(m_RSVStr[l_arrIter],::G_CheckForVar(m_RSVStr[l_arrIter]));
			l_bothVal[l_arrIter] = l_strRSV.M_GetValue();
		}
		M_PerfOper<std::string>(l_bothVal[0],l_bothVal[1]);
	}
public:
	std::string m_condStr;
	void M_Init(void) {
		M_GetValOfFirstComp();
		M_GetOperand();
		M_GetValOfScndComp();

		m_arrComparFunc[0] = &Condition::M_CompSzet;
		m_arrComparFunc[1] = &Condition::M_CompChar;
		m_arrComparFunc[2] = &Condition::M_CompBool;
		m_arrComparFunc[3] = &Condition::M_CompStr;
	}
	const bool M_Compare(void) {
		M_GetTypeOfCond();
		(*this.*m_arrComparFunc[m_typeOfCond])();
		return m_isCondTrue;
	}
	void M_Update(const std::string& p_newCond) {
		m_condStr = p_newCond;
		m_RSVStr[0] = "";
		m_RSVStr[1] = "";
		M_GetValOfFirstComp();
		M_GetValOfScndComp();
	}
private:
	enum operand {
		equ = 0,
		grt = 1,
		less = 2,
		notequ = 3
	};
	operand m_operOfCond;
	bool m_isCondTrue;
	bool m_isVar[2] = {false,false};
	std::string m_RSVStr[2] = {"",""};
	type m_typeOfCond;
	typedef void(Condition::*func_ptr)(void);
	func_ptr m_arrComparFunc[4];
};

#endif
