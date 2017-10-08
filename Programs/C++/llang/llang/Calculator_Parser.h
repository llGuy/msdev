#ifndef _CALC_PARSER
#define _CALC_PARSER

#include "Misc.h"
#include "CNSTMacros.h"

class Parser {
private:
	typedef std::string(Parser::*func_operation)(const std::string&) const;
	const char m_CHAR_OPERATORS[5];
	func_operation m_operations[5];
	std::string m_strOperation;
private:
	size_t* M_ExtractValuesOfOperation(const std::string& p_expression) const {
		std::string l_arrOfTermsStr[2];
		size_t* l_values = new size_t[2];
		size_t l_strIter = _NULL;
		size_t l_szeOfArr = _NULL;
		while(p_expression[l_strIter] != '\0') {
			if(p_expression[l_strIter] == ' ') {
				l_strIter += 3;
				l_szeOfArr++;
			}
			if((size_t)p_expression[l_strIter] >= ::g_0ASCII && (size_t)p_expression[l_strIter] <= ::g_9ASCII)
				l_arrOfTermsStr[l_szeOfArr] += p_expression[l_strIter];
			l_strIter++;
		}
		for(size_t l_arrIter = 0; l_arrIter < 2; l_arrIter++)
			l_values[l_arrIter] = ::G_ExtractValueOfStrUInt(l_arrOfTermsStr[l_arrIter]);
		return l_values;
	}
protected:
	std::string M_Add(const std::string& p_expression) const {
		size_t* l_values = M_ExtractValuesOfOperation(p_expression);
		size_t l_resultOfAddition = l_values[0] + l_values[1];
		delete[] l_values;
		return G_ConvertUIntToStr(l_resultOfAddition);
	}
	std::string M_Sub(const std::string& p_expression) const {
		size_t* l_values = M_ExtractValuesOfOperation(p_expression);
		size_t l_resultOfAddition = l_values[0] - l_values[1];
		delete[] l_values;
		return G_ConvertUIntToStr(l_resultOfAddition);
	}
	std::string M_Mul(const std::string& p_expression) const {
		size_t* l_values = M_ExtractValuesOfOperation(p_expression);
		size_t l_resultOfAddition = l_values[0] * l_values[1];
		delete[] l_values;
		return G_ConvertUIntToStr(l_resultOfAddition);
	}
	std::string M_Div(const std::string& p_expression) const {
		size_t* l_values = M_ExtractValuesOfOperation(p_expression);
		size_t l_resultOfAddition = l_values[0] / l_values[1];
		delete[] l_values;
		return G_ConvertUIntToStr(l_resultOfAddition);
	}
	std::string M_Mod(const std::string& p_expression) const {
		size_t* l_values = M_ExtractValuesOfOperation(p_expression);
		size_t l_resultOfAddition = l_values[0] % l_values[1];
		delete[] l_values;
		return G_ConvertUIntToStr(l_resultOfAddition);
	}
protected:
	inline std::string M_ParseStrPrev(size_t p_indexOfEnd,const std::string& p_expression) const {
		std::string l_result;
		size_t l_indexOfExp = _NULL;
		while(l_indexOfExp < p_indexOfEnd) {
			l_result += p_expression[l_indexOfExp];
			l_indexOfExp++;
		}
		return l_result;
	}
	inline std::string M_ParseStrAfter(size_t p_indexOfStart,const std::string& p_expression,bool p_var = false) const {
		std::string l_resultStr;
		size_t l_indexOfExp = p_indexOfStart;
		if(p_expression[l_indexOfExp] == '\0') return l_resultStr;
		else if(p_expression[l_indexOfExp + 1] == '\0') {
			if(p_var) return l_resultStr + p_expression[l_indexOfExp];
			else return l_resultStr;
		}
		else if(p_expression[l_indexOfExp] != '\0') {
			l_indexOfExp = p_indexOfStart;
			while(p_expression[l_indexOfExp] != '\0') {
				l_resultStr += p_expression[l_indexOfExp];
				l_indexOfExp++;
			}
		}
		return l_resultStr;
	}
protected:
	std::string M_UpdateExp(Vector<std::string>& p_vecOfWords,
		size_t p_indexOfExpression,std::string& p_resultOfOperation) {
		//result of the update
		std::string l_updatedStr;
		std::string l_temp;
		//iterates through the vector or words
		for(size_t l_vecIter = 0; l_vecIter < p_vecOfWords.m_size; l_vecIter++) {
			//if it's an operation or a bracket
			if((size_t)p_vecOfWords[l_vecIter][0] >= g_0ASCII && (size_t)p_vecOfWords[l_vecIter][0] <= g_9ASCII)
				l_temp += p_vecOfWords[l_vecIter];
			//if the index is the index of the expression being updated
			if(l_vecIter == p_indexOfExpression) {
				l_temp = p_resultOfOperation;
				l_vecIter++;
			}
			//if it's at an odd index a.k.a an operation and if 
			//the index isn't at the index of the expression
			if((l_vecIter % 2 == 1 || l_vecIter == p_vecOfWords.m_size - 1) && l_vecIter != p_indexOfExpression) {
				if(l_vecIter != p_vecOfWords.m_size - 1) {
					l_updatedStr += l_temp + p_vecOfWords[l_vecIter] + ' ';
					l_temp = "";
				}
				else l_updatedStr += l_temp;
				continue;
			}
			if(l_vecIter != p_vecOfWords.m_size - 1) l_temp += ' ';
		}
		return l_updatedStr;
	}
	std::string M_CheckAndExtractVariable(std::string p_expression) {
		size_t l_indexOfExp = _NULL;
		size_t l_indexOfVarEnd = _NULL;
		size_t l_indexOfVarStart = _NULL;
		std::string l_temp;
		std::string l_expAfterVar;
		std::string l_expBeforeVar;
		bool l_foundVar = false;
		while(p_expression[l_indexOfExp] != '\0') {
			unsigned char l_currentChar = p_expression[l_indexOfExp];
			//abbreviation
			unsigned char l_cc = l_currentChar;
			if(l_cc != '(' && l_cc != ')') {
				if(((size_t)l_cc < g_0ASCII || (size_t)l_cc > g_9ASCII) &&
					(l_cc != '+' && l_cc != '-' && l_cc != '*' &&l_cc != '/'&&l_cc != '%' && l_cc != ' ')) {
					l_temp += l_cc;
					if(!l_foundVar) l_indexOfVarStart = l_indexOfExp;
					l_foundVar = true;
				}
			}
			if(l_foundVar) {
				if(l_cc == ' ' || l_cc == '(' || l_cc == ')' || l_cc == '\0') { 
					l_indexOfVarEnd = l_indexOfExp;
					l_expBeforeVar = M_ParseStrPrev(l_indexOfVarStart,p_expression);
					l_expAfterVar = M_ParseStrAfter(l_indexOfVarEnd,p_expression,true);
					p_expression = l_expBeforeVar +
						::G_ConvertUIntToStr(VarHT::M_Shared().m_hTableOfSzet.M_FindVariable(l_temp)->m_value) + l_expAfterVar;
					return M_CheckAndExtractVariable(p_expression);
				}
				else if(p_expression[l_indexOfExp + 1] == '\0') {
					l_expBeforeVar = M_ParseStrPrev(l_indexOfVarStart,p_expression);
					p_expression = l_expBeforeVar + 
						::G_ConvertUIntToStr(VarHT::M_Shared().m_hTableOfSzet.M_FindVariable(l_temp)->m_value);
					return M_CheckAndExtractVariable(p_expression);
				}
			}
			l_indexOfExp++;
		}
		return p_expression;
	}
protected:
	std::string M_Reduce(std::string& p_currentExp,
		std::string p_originalStrBeforeIndex,std::string p_originalStrAfterIndex,size_t p_quantOfBrackets = 0) {
		if(G_CalculateQuantOfWords(p_currentExp) > 1) {
			size_t l_quantOpenBrackets = _NULL;
			size_t l_quantClosedBrackets = _NULL;
			size_t l_indexOpenBrackets = _NULL;
			size_t l_indexOfExp = _NULL;
			std::string l_temp;
			while(p_currentExp[l_indexOfExp] != '\0') {
				if(p_currentExp[l_indexOfExp] == '(') {
					if(l_quantOpenBrackets == 0) {
						l_quantOpenBrackets++;
						l_indexOpenBrackets = l_indexOfExp;
						l_indexOfExp++;
						l_temp += p_currentExp[l_indexOfExp];
					}
					else {
						l_quantOpenBrackets++;
						l_temp += p_currentExp[l_indexOfExp];
					}
				}
				else if(p_currentExp[l_indexOfExp] == ')') {
					l_quantClosedBrackets++;
					if(l_quantOpenBrackets == l_quantClosedBrackets) {
						if(l_quantOpenBrackets > 1) {
							p_originalStrBeforeIndex = M_ParseStrPrev(l_indexOpenBrackets + 1,p_currentExp);
							p_originalStrAfterIndex = M_ParseStrAfter(l_indexOfExp,p_currentExp);
						}
						else {
							p_originalStrBeforeIndex = M_ParseStrPrev(l_indexOpenBrackets,p_currentExp);
							p_originalStrAfterIndex = M_ParseStrAfter(l_indexOfExp + 1,p_currentExp);
						}
						return M_Reduce(l_temp,p_originalStrBeforeIndex,p_originalStrAfterIndex,l_quantOpenBrackets);
					}
					else l_temp += p_currentExp[l_indexOfExp];
				}
				else if(l_quantOpenBrackets > 0) l_temp += p_currentExp[l_indexOfExp];
				l_indexOfExp++;
			}
			Vector<std::string> l_vecWords;
			std::string l_tempWord;
			l_indexOfExp = 0;
			while(p_currentExp[l_indexOfExp] != '\0') {
				if(p_currentExp[l_indexOfExp] != ' ') l_tempWord += p_currentExp[l_indexOfExp];
				if(p_currentExp[l_indexOfExp] == ' '||p_currentExp[l_indexOfExp + 1] == '\0') {
					l_vecWords.M_PushBack(l_tempWord);
					l_tempWord = "";
				}
				l_indexOfExp++;
			}
			std::string l_resultOfAnOperation;
			size_t l_indexOfOperation = 0;
			for(size_t l_vecIter = 0; l_vecIter < l_vecWords.m_size; l_vecIter++) {
				for(size_t l_typesOfOper = 0; l_typesOfOper < 5; l_typesOfOper++) {
					if(l_vecWords[l_vecIter][0] == m_CHAR_OPERATORS[l_typesOfOper] && (m_CHAR_OPERATORS[l_typesOfOper] == '*'||
						m_CHAR_OPERATORS[l_typesOfOper] == '/' && m_CHAR_OPERATORS[l_typesOfOper] == '%')) {
						std::string l_term1 = l_vecWords[l_vecIter - 1];
						std::string l_term2 = l_vecWords[l_vecIter];
						std::string l_term3 = l_vecWords[l_vecIter + 1];
						std::string l_operation = l_term1 + ' ' + l_term2 + ' ' + l_term3;
						l_resultOfAnOperation = (*this.*m_operations[l_typesOfOper])(l_operation);
						l_indexOfOperation = l_vecIter;
						goto MUL_DIV;
					}
				}
			}
	MUL_DIV:if(l_resultOfAnOperation != "") {
				std::string l_updatedString = M_UpdateExp(l_vecWords,l_indexOfOperation,l_resultOfAnOperation);
				if(l_updatedString == "") return M_Reduce(l_resultOfAnOperation,
					p_originalStrBeforeIndex,p_originalStrAfterIndex,p_quantOfBrackets);
				else return M_Reduce(l_updatedString,
					p_originalStrBeforeIndex,p_originalStrAfterIndex,p_quantOfBrackets);
			}
			l_resultOfAnOperation = "";
			for(size_t l_vecIter = 0; l_vecIter < l_vecWords.m_size; l_vecIter++) {
				for(size_t l_typesOfOper = 0; l_typesOfOper < l_vecWords.m_size; l_typesOfOper++) {
					if(l_vecWords[l_vecIter][0] == m_CHAR_OPERATORS[l_typesOfOper] && (m_CHAR_OPERATORS[l_typesOfOper] == '+' ||
						m_CHAR_OPERATORS[l_typesOfOper] == '-')) {
						std::string l_term1 = l_vecWords[l_vecIter - 1];
						std::string l_term2 = l_vecWords[l_vecIter];
						std::string l_term3 = l_vecWords[l_vecIter + 1];
						std::string l_operation = l_term1 + ' ' + l_term2 + ' ' + l_term3;
						l_resultOfAnOperation = (*this.*m_operations[l_typesOfOper])(l_operation);
						l_indexOfOperation = l_vecIter;
						goto ADD_SUB;
					}
				}
			}
	ADD_SUB:std::string l_updatedExp;
			if(l_vecWords.m_size == 3) l_updatedExp = l_resultOfAnOperation;
			else l_updatedExp = M_UpdateExp(l_vecWords,l_indexOfOperation,l_resultOfAnOperation);
			return M_Reduce(l_updatedExp,
				p_originalStrBeforeIndex,p_originalStrAfterIndex,p_quantOfBrackets);
		}
		else {
			if(p_quantOfBrackets == 0) return p_currentExp;
			else {
				p_quantOfBrackets--;
				p_originalStrBeforeIndex = M_ParseStrPrev(p_originalStrBeforeIndex.length(),p_originalStrBeforeIndex);
				p_originalStrAfterIndex = M_ParseStrAfter(0,p_originalStrAfterIndex);
				if(p_originalStrAfterIndex == "") p_currentExp = p_originalStrBeforeIndex + p_currentExp + p_originalStrAfterIndex;
				else p_currentExp = p_originalStrBeforeIndex + p_currentExp + p_originalStrAfterIndex + ' ';
				return M_Reduce(p_currentExp,"","",p_quantOfBrackets);
			}
		}
	}
public:
	explicit Parser(const std::string& p_strOperation) 
		: m_strOperation(p_strOperation),m_CHAR_OPERATORS{'+','-','*','/','%'}
	{
		m_operations[0] = &Parser::M_Add;
		m_operations[1] = &Parser::M_Sub;
		m_operations[2] = &Parser::M_Mul;
		m_operations[3] = &Parser::M_Div;
		m_operations[4] = &Parser::M_Mod;
	}
	~Parser(void)
	{
	}
public:
	size_t M_Calculate(void) {
		m_strOperation = M_CheckAndExtractVariable(m_strOperation);
		size_t l_answer = ::G_ExtractValueOfStrUInt(M_Reduce(m_strOperation,"",""));
		return l_answer;
	}
};

#endif