#ifndef _CONDITION
#define _CONDITION

#include "../../../misc/Misc.h"
#include "../../../rsv/IncludeRSV.h"

//condition class responsible for comparing items / values
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
	//gets the values of the components (e.g. 12, 'a', "hello world!")
	void M_GetValOfFirstComp(void) { 
		m_RSVStr[0] = ::G_BuildString(']',1,m_condStr); }
	void M_GetValOfScndComp(void) { 
		m_RSVStr[1] = ::G_BuildString(']',1 + m_RSVStr[0].length() + 5,m_condStr); };
	
	//gets the operator of the comparison (e.g. '>', '<')
	void M_GetOperator(void) {
		//l_operatorChr = the char at the position at which
		//the operator would be
		char l_operatorChr = m_condStr[1 + m_RSVStr[0].length() + 2];

		//usese the unordered_map which contains all the operators as chars
		//which correspond to the oper value
		for(auto l_operMapIter = Oper::M_Shared().m_mapOperChar.begin(); 
			l_operMapIter != Oper::M_Shared().m_mapOperChar.end(); ++l_operMapIter) {
			if(l_operMapIter->second == l_operatorChr) {
				m_operOfCond = l_operMapIter->first;
				return;
			}
		}
	}
	//gets the type of which the comparison is dealing with
	void M_GetTypeOfCond(void) {
		for(size_t l_arrRSVIter = 0; l_arrRSVIter < 2; l_arrRSVIter++) {
			//the string version of the RSV doesn't correspond to a const
			//like 12,'a' or "hello world!", G_FetchTypeOfConst will return
			//type_default
			type l_tempType = ::G_FetchTypeOfConst(m_RSVStr[l_arrRSVIter]);
			if(l_tempType == type_default) {
				//if there are spaces, the RSV is an operation
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
				m_typeOfCond = l_tempType;
				return;
			}
		}
	}
	//templated function actually compares the two values
	template<typename T>
	const bool M_PerfOper(T p_comp1,T p_comp2) {
		//Oper has an unordered_map of lambdas which contains the 
		//methods to compare the values given a specific type of operator
		Oper::M_Shared().m_mapOperLam[equ] = [=](void)->bool {return p_comp1 == p_comp2; };
		Oper::M_Shared().m_mapOperLam[grt] = [=](void)->bool {return p_comp1 > p_comp2; };
		Oper::M_Shared().m_mapOperLam[less] = [=](void)->bool {return p_comp1 < p_comp2; };
		Oper::M_Shared().m_mapOperLam[notequ] = [=](void)->bool {return p_comp1 != p_comp2; };
		m_isCondTrue = Oper::M_Shared().m_mapOperLam[m_operOfCond]();
		return m_isCondTrue;
	}
private:
	//following functions compare items of different types
	void M_CompSzet(void) {
		size_t l_bothVal[2];
		//extract the values of the components
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
		//compare
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
	//function initializes the Condition
	void M_Init(void) {
		M_GetValOfFirstComp();
		M_GetOperator();
		M_GetValOfScndComp();

		m_arrComparFunc[0] = &Condition::M_CompSzet;
		m_arrComparFunc[1] = &Condition::M_CompChar;
		m_arrComparFunc[2] = &Condition::M_CompBool;
		m_arrComparFunc[3] = &Condition::M_CompStr;
	}
	//returns a bool which corresponds to the result
	//of the comparison
	const bool M_Compare(void) {
		M_GetTypeOfCond();
		(*this.*m_arrComparFunc[m_typeOfCond])();
		return m_isCondTrue;
	}
	//if the components change in value,
	//one must call this function to renew the Condition object
	//with the new values of the components
	void M_Update(const std::string& p_newCond) {
		m_condStr = p_newCond;
		m_RSVStr[0] = "";
		m_RSVStr[1] = "";
		M_GetValOfFirstComp();
		M_GetValOfScndComp();
	}
private:
	enum oper {
		equ = 0,
		grt = 1,
		less = 2,
		notequ = 3
	};
	oper m_operOfCond;
	bool m_isCondTrue;
	bool m_isVar[2] = {false,false};
	std::string m_RSVStr[2] = {"",""};
	type m_typeOfCond;
	typedef void(Condition::*func_ptr)(void);
	func_ptr m_arrComparFunc[4];
	//contains unordered_map with operator and their char equivalent
	struct Oper {
		std::unordered_map<oper,char> m_mapOperChar;
		std::unordered_map<oper,std::function<bool(void)>> m_mapOperLam;
	public:
		void M_Init(void) {
			m_mapOperChar[equ] = '=';
			m_mapOperChar[grt] = '>';
			m_mapOperChar[less] = '<';
			m_mapOperChar[notequ] = '!';
		}
	public:
		static Oper& M_Shared(void) {
			static Oper* l_singl = nullptr;
			if(l_singl == nullptr) {
				l_singl = new Oper();
				l_singl->M_Init();
			}
			return *l_singl;
		}
	};
};

#endif
