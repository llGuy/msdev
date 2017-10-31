#ifndef _MISC
#define _MISC

#include <unordered_map>
#include <functional>
#include <iostream>
#include <fstream>
#include <string>

#include "../var-storage/VarHTables.h"

extern const size_t g_0ASCII = 48;
extern const size_t g_9ASCII = 57;

enum type {
	type_int,
	type_char,
	type_bool,
	type_str,
	type_default
};
extern std::string G_BuildString(const char p_endCh,size_t p_szetIter,const std::string& p_strOri) {
	std::string l_strDest = "";
	while(p_strOri[p_szetIter] != p_endCh && p_szetIter < p_strOri.length()) {
		l_strDest += p_strOri[p_szetIter];
		p_szetIter++;
	}
	return l_strDest;
}
extern inline size_t G_GetQuantOfDigits(size_t p_uint) {
	if(p_uint == 0) return 1;
	size_t l_count = 0;
	while(p_uint != 0) {
		p_uint /= 10;
		l_count++;
	}
	return l_count;
}
extern inline size_t G_Power(int p_base,int p_exp) {
	if(p_exp == 0) return 1;
	if(p_exp == 1) return p_base;
	if(p_exp > 1) {
		unsigned int l_result = 1;
		for(int l_expIter = 0; l_expIter < p_exp; l_expIter++)
			l_result = l_result * p_base;
		return l_result;
	}
	else return 1;
}
extern inline size_t G_ExtractValueOfStrUInt(const std::string& p_strUInt) {
	size_t l_lengthOfStr = p_strUInt.length();
	size_t l_valueOfUInt = 0;
	for(size_t l_digitOfUInt = 0; l_digitOfUInt < l_lengthOfStr; l_digitOfUInt++)
		l_valueOfUInt += (size_t)(p_strUInt[l_digitOfUInt] - 48) * G_Power(10,l_lengthOfStr - l_digitOfUInt - 1);
	return l_valueOfUInt;
}
extern inline std::string G_ConvertUIntToStr(size_t p_uint) {
	std::string l_strOfUInt;
	size_t l_quantOfDigits = G_GetQuantOfDigits(p_uint);
	char* l_arrOfDigits = new char[l_quantOfDigits];
	for(size_t l_digitIter = 0; l_digitIter < l_quantOfDigits; l_digitIter++) {
		l_arrOfDigits[l_digitIter] = static_cast<char>(p_uint % 10 + g_0ASCII);
		p_uint /= 10;
	}
	for(size_t l_digitIter = l_quantOfDigits; l_digitIter > 0; l_digitIter--)
		l_strOfUInt += l_arrOfDigits[l_digitIter - 1];
	return l_strOfUInt;
}
extern inline size_t G_CalculateQuantOfWords(const std::string& p_str) {
	size_t l_index = 0;
	size_t l_quantOfWords = 1;
	while(p_str[l_index] != '\0') {
		if(p_str[l_index] == ' ') l_quantOfWords++;
		l_index++;
	}
	return l_quantOfWords;
}
extern inline bool G_CheckForVar(const std::string& p_RSVStr) {
	bool l_criteriaToPass[] = {
		true,
		false,
		false,
		false
	};
	bool l_isVar = true;
	if(p_RSVStr == "true" || p_RSVStr == "false") l_criteriaToPass[0] = false;
	if(p_RSVStr[0] != '\'') l_criteriaToPass[1] = true;
	if(p_RSVStr[0] != '\"') l_criteriaToPass[2] = true;
	if(static_cast<size_t>(p_RSVStr[0]) < g_0ASCII || static_cast<size_t>(p_RSVStr[0]) > g_9ASCII)
		l_criteriaToPass[3] = true;
	for(size_t l_arrIter = 0; l_arrIter < 4; l_arrIter++)
		l_isVar = l_isVar & l_criteriaToPass[l_arrIter];
	return l_isVar;
}

extern inline type G_FetchTypeOfVar(const std::string& p_varStr) {
	bool l_isVarInTypeHTable[5] = {
		p_varStr == VarHT::M_Shared().m_hTableOfSzet.M_FindVariable(p_varStr)->M_ID(),
		p_varStr == VarHT::M_Shared().m_hTableOfChar.M_FindVariable(p_varStr)->M_ID(),
		p_varStr == VarHT::M_Shared().m_hTableOfBool.M_FindVariable(p_varStr)->M_ID(),
		p_varStr == VarHT::M_Shared().m_hTableOfStr.M_FindVariable(p_varStr)->M_ID(),
		true
	};
	type l_types[5]{
		type_int,
		type_char,
		type_bool,
		type_str,
		type_default
	};

	for(size_t l_arrIter = 0; l_arrIter < 5; l_arrIter++) {
		if(l_isVarInTypeHTable[l_arrIter]) return l_types[l_arrIter];
	}
	return type_default;
}
extern inline type G_FetchTypeOfConst(const std::string& p_RSVStr) {
	type l_typeOfRSV = type_default;
	if(p_RSVStr == "true" || p_RSVStr == "false")
		l_typeOfRSV = type_bool;
	else if(p_RSVStr[0] == '\'')
		l_typeOfRSV = type_char;
	else if(p_RSVStr[0] == '\"')
		l_typeOfRSV = type_str;
	else if((size_t)p_RSVStr[0] >= g_0ASCII && (size_t)p_RSVStr[0] <= g_9ASCII)
		l_typeOfRSV = type_int;
	return l_typeOfRSV;
}
#endif
