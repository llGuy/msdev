#ifndef _TEST
#define _TEST

#include "Misc.h"
#include "HTable.h"
#include "Vector.h"
#include "Program.h"
#include "RSV_Const.h"
#include "Condition.h"
#include "IncludeCLine.h"
#include "Calculator_Parser.h"

class Test {
public:
	explicit Test(void)
	{
	}
	~Test(void)
	{
	}
public:
	void PerformTest(void) const {
		M_TestVector();
		M_TestHTable();
		M_TestParser();
		M_TestSetSzetConst();
		M_TestSetSzetVariable();
		M_TestSetSzetOperation();
		M_TestSetSzetOperationM();
		M_TestSetCharConst();
		M_TestSetCharVariable();
		M_TestSetBoolConst();
		M_TestSetBoolVariable();
		M_TestSetStringConst();
		M_TestSetStringVariable();
		M_TestModSzetConst();
		M_TestModSzetVariable();
		M_TestModSzetOperation(); 
		M_TestModChar();
		M_TestModString();
		M_TestPrintSzet();
		M_TestPrintChar();
		//M_TestInput();
		M_TestSaveSzet();
		M_TestSaveChar();
		M_TestSaveBool();
		//M_TestSaveStr();
		//M_TestReadSzet();
		//M_TestReadChar();
		//M_TestReadBool();
		//M_TestReadStr();
		M_TestCondition();
		M_TestForLoop();
	}

	template<typename T>
	void M_AssertEqual(const char* p_comment,const char* p_type,T p_t1,T p_t2) const {
		std::cout << "> " << p_comment << " : ";
		std::string l_ult = p_t1 == p_t2 ? "SUCCESS" : "FAILURE";
		std::cout << l_ult << std::endl;
		std::cout << "	" << p_type << " 1 = " << p_t1 << " | " << p_type << " 2 = " << p_t2 << std::endl;
		std::cout << std::endl;
	}
	void M_TestVector(void) const {
		std::cout << "> testing vector : \n";
		Vector<int> l_vec;
		for(size_t l_index = 0; l_index < 12; l_index++) {
			l_vec.M_PushBack(l_index);
			std::cout << "	value " << l_index << " : " << l_vec[l_index] << std::endl;
		}
		//copy the vector l_vec2
		std::cout << "\n	copying vector : ";
		Vector<int> l_vec2;
		l_vec2.M_PushBack(12);
		l_vec(l_vec2);
		std::cout << l_vec[0] << std::endl;
		std::cout << std::endl;
	}
	void M_TestHTable(void) const {
		std::cout << "> testing hash table : \n";
		htble::HTable<int> htable;
		std::string name ="hi";
		int val = 12;
		htable.M_AppendVar(val,name);
		std::cout << "	" << htable.M_FindVariable(name)->m_name << std::endl;
		for(size_t l_index = 0; l_index < 5; l_index++) {
			htable.M_AppendVar(val,name);
		}
		std::string name1 ="ho";
		int val1 = 13;
		htable.M_AppendVar(val1,name1);
		std::cout << "	quant of the htable : " << htable.M_GetQuantOfHTable();
		std::cout << std::endl;
		std::cout << "	" << htable.M_FindVariable(name1)->m_value << std::endl;
		std::cout << std::endl;
	}
	void M_TestParser(void)  const {
		std::string l_operation = "3 * (60 - 12) - 1";
		Parser l_parser(l_operation);
		M_AssertEqual<size_t>("> testing parser : ","size_t",3 * (60 - 12) - 1,l_parser.M_Calculate());
	}
	void M_TestSetSzetConst(void) const {
		std::string l_setLine1 = "set int a = 1;";
		CLine::LineOfCode* l_setConstSzet = new CLine::LineOfCode_Set(l_setLine1);
		l_setConstSzet->M_Translate();
		M_AssertEqual<size_t>("> testing set line of code for const int :","size_t",1,
			VarHT::M_Shared().m_hTableOfSzet.M_FindVariable("a")->m_value);
	}
	void M_TestSetSzetVariable(void) const {
		std::string l_setLine2 = "set int b = a;";
		CLine::LineOfCode* l_setVarSzet = new CLine::LineOfCode_Set(l_setLine2);
		l_setVarSzet->M_Translate();
		M_AssertEqual<size_t>("> testing set line of code for variable int :","sizet",1,
			VarHT::M_Shared().m_hTableOfSzet.M_FindVariable("b")->m_value);
	}
	void M_TestSetSzetOperation(void) const {
		std::string l_setLine3 = "set int c = 3 * (60 - 12) - 1;";
		CLine::LineOfCode* l_setOperationSzet = new CLine::LineOfCode_Set(l_setLine3);
		l_setOperationSzet->M_Translate();
		M_AssertEqual<size_t>("> testing set line of code for operaiton int :","size_t",143,
			VarHT::M_Shared().m_hTableOfSzet.M_FindVariable("c")->m_value);
	}
	void M_TestSetSzetOperationM(void) const {
		std::string l_setLineM = "set int bar = c + 1 - 1;";
		CLine::LineOfCode* l_setOperationSzet = new CLine::LineOfCode_Set(l_setLineM);
		l_setOperationSzet->M_Translate();
		M_AssertEqual<size_t>("> testing set line of code for operaiton int :","size_t",3 * (60 - 12) - 1 + 1 - 1,
			VarHT::M_Shared().m_hTableOfSzet.M_FindVariable("c")->m_value);
	}
	void M_TestSetCharConst(void) const {
		std::string l_setLine4 = "set char d = \'a\';";
		CLine::LineOfCode* l_setConstChar = new CLine::LineOfCode_Set(l_setLine4);
		l_setConstChar->M_Translate();
		M_AssertEqual<char>("> testing set line of code for const char :","char",'a',
			VarHT::M_Shared().m_hTableOfChar.M_FindVariable("d")->m_value);
	}
	void M_TestSetCharVariable(void) const {
		std::string l_setLine5 = "set char e = d;";
		CLine::LineOfCode* l_setVariableChar = new CLine::LineOfCode_Set(l_setLine5);
		l_setVariableChar->M_Translate();
		M_AssertEqual<char>("> testing set line of code for variable char :","char",'a',
			VarHT::M_Shared().m_hTableOfChar.M_FindVariable("e")->m_value);
	}
	void M_TestSetBoolConst(void) const {
		std::string l_setLine6 = "set bool f = true;";
		CLine::LineOfCode* l_setConstBool = new CLine::LineOfCode_Set(l_setLine6);
		l_setConstBool->M_Translate();
		M_AssertEqual<bool>("> testing set line of code for const bool :","bool",true,
			VarHT::M_Shared().m_hTableOfBool.M_FindVariable("f")->m_value);
	}
	void M_TestSetBoolVariable(void) const {
		std::string l_setLine7 = "set bool g = f;";
		CLine::LineOfCode* l_setConstBool = new CLine::LineOfCode_Set(l_setLine7);
		l_setConstBool->M_Translate();
		M_AssertEqual<bool>("> testing set line of code for variable bool :","bool",true,
			VarHT::M_Shared().m_hTableOfBool.M_FindVariable("g")->m_value);
	}
	void M_TestSetStringConst(void) const {
		std::string l_setLine8 = "set string h = \"hello world\";";
		CLine::LineOfCode* l_setConstString = new CLine::LineOfCode_Set(l_setLine8);
		l_setConstString->M_Translate();
		M_AssertEqual<std::string>("> testing set line of code for const string :","string","hello world",
			VarHT::M_Shared().m_hTableOfStr.M_FindVariable("h")->m_value);
	}
	void M_TestSetStringVariable(void) const {
		std::string l_setLine9 = "set string i = h;";
		CLine::LineOfCode* l_setVariableString = new CLine::LineOfCode_Set(l_setLine9);
		l_setVariableString->M_Translate();
		M_AssertEqual<std::string>("> testing set line of code for variable string :","string","hello world",
			VarHT::M_Shared().m_hTableOfStr.M_FindVariable("i")->m_value);
	}
	void M_TestModSzetConst(void) const {
		std::string l_modLine1 = "mod a -> 42;";
		CLine::LineOfCode* l_modConstSzet = new CLine::LineOfCode_Mod(l_modLine1);
		l_modConstSzet->M_Translate();
		M_AssertEqual<size_t>("> testing mod line of code for constant szet :","szet",42,
			VarHT::M_Shared().m_hTableOfSzet.M_FindVariable("a")->m_value);
	}
	void M_TestModSzetVariable(void) const {
		std::string l_modLine2 = "mod a -> b;";
		CLine::LineOfCode* l_modVariableSzet = new CLine::LineOfCode_Mod(l_modLine2);
		l_modVariableSzet->M_Translate();
		M_AssertEqual<size_t>("testing mod line of code for variable szet :","szet",
			VarHT::M_Shared().m_hTableOfSzet.M_FindVariable("b")->m_value,
			VarHT::M_Shared().m_hTableOfSzet.M_FindVariable("a")->m_value);
	}
	void M_TestModSzetOperation(void) const {
		std::string l_modLine3 = "mod a -> b + 42 * 1;";
		CLine::LineOfCode* l_modOperationSzet = new CLine::LineOfCode_Mod(l_modLine3);
		l_modOperationSzet->M_Translate();
		M_AssertEqual<size_t>("testing mod line of code for operation szet :","szet",1 + 42 * 1,
			VarHT::M_Shared().m_hTableOfSzet.M_FindVariable("a")->m_value);
	}
	void M_TestModChar(void) const {
		std::string l_modLine4 = "mod e -> \'e\';";
		CLine::LineOfCode* l_modChar = new CLine::LineOfCode_Mod(l_modLine4);
		l_modChar->M_Translate();
		M_AssertEqual<char>("testing mod line of code for char :","char",'e',
			VarHT::M_Shared().m_hTableOfChar.M_FindVariable("e")->m_value);
	}
	void M_TestModString(void) const {
		std::string l_modLine5 = "mod h -> \"the answer to life is 42\";";
		CLine::LineOfCode* l_modString = new CLine::LineOfCode_Mod(l_modLine5);
		l_modString->M_Translate();
		M_AssertEqual<std::string>("testing mod line of code for string :","string",
			"the answer to life is 42",VarHT::M_Shared().m_hTableOfStr.M_FindVariable("h")->m_value);
	}
	void M_TestPrintSzet(void) const {
		std::cout << "> testing print szet :\n	";
		std::string l_printLine1 = "print 12;";
		CLine::LineOfCode* l_printSzet = new CLine::LineOfCode_Print(l_printLine1);
		l_printSzet->M_Translate();
		std::cout << std::endl;
		std::cout << std::endl;
	}
	void M_TestPrintChar(void) const {
		std::cout << "> testing print char :\n	";
		std::string l_printLine2 = "print \'a\';";
		CLine::LineOfCode* l_printChar = new CLine::LineOfCode_Print(l_printLine2);
		l_printChar->M_Translate();
		std::cout << std::endl;
		std::cout << std::endl;
	}
	void M_TestInput(void) const {
		std::cout << "> testing input :\n	";
		std::string l_inputLine1 = "input a;";
		CLine::LineOfCode* l_input = new CLine::LineOfCode_Input(l_inputLine1);
		l_input->M_Translate();
		std::string l_printLine3 = "print a;";
		CLine::LineOfCode* l_printSzet = new CLine::LineOfCode_Print(l_printLine3);
		std::cout << "	";
		l_printSzet->M_Translate();
		std::cout << std::endl;
	}
	void M_TestSaveSzet(void) const {
		std::cout << "> testing file saving with szet :\n";
		std::string l_saveLine1 = "save \"test1.txt\" a;";
		CLine::LineOfCode* l_save = new CLine::LineOfCode_Save(l_saveLine1);
		l_save->M_Translate();
		std::cout << "	saved to file test1.txt" << std::endl;
		std::cout << std::endl;
	}
	void M_TestSaveChar(void) const {
		std::cout << "> testing file saving with char :\n";
		std::string l_saveLine2 = "save \"test2.txt\" \'a\';";
		CLine::LineOfCode* l_save = new CLine::LineOfCode_Save(l_saveLine2);
		l_save->M_Translate();
		std::cout << "	saved to file test2.txt" << std::endl;
		std::cout << std::endl;
	}
	void M_TestSaveBool(void) const {
		std::cout << "> testing file saving with bool :\n";
		std::string l_saveLine3 = "save \"test3.txt\" true;";
		CLine::LineOfCode* l_save = new CLine::LineOfCode_Save(l_saveLine3);
		l_save->M_Translate();
		std::cout << "	saved to file test3.txt" << std::endl;
		std::cout << std::endl;
	}
	void M_TestSaveStr(void) const {
		std::cout << "> testing file saving with strings :\n";
		std::string l_saveLine4 = "save \"test4.txt\" i;";
		CLine::LineOfCode* l_save = new CLine::LineOfCode_Save(l_saveLine4);
		l_save->M_Translate();
		std::cout << "	saved to file test4.txt" << std::endl;
		std::cout << std::endl;
	}
	void M_TestReadSzet(void) const {
		std::string l_readLine1 = "read \"test1.txt\" a;";
		CLine::LineOfCode* l_read = new CLine::LineOfCode_Read(l_readLine1);
		l_read->M_Translate();
		M_AssertEqual<size_t>("testing read line of code for szet :","szet",43,
			VarHT::M_Shared().m_hTableOfSzet.M_FindVariable("a")->m_value);
	}
	void M_TestReadChar(void) const {
		std::string l_readLine2 = "read \"test2.txt\" d;";
		CLine::LineOfCode* l_read = new CLine::LineOfCode_Read(l_readLine2);
		l_read->M_Translate();
		M_AssertEqual<char>("testing read line of code for char :","char",'a',
			VarHT::M_Shared().m_hTableOfChar.M_FindVariable("d")->m_value);
	}
	void M_TestReadBool(void) const {
		std::string l_readLine3 = "read \"test3.txt\" f;";
		CLine::LineOfCode* l_read = new CLine::LineOfCode_Read(l_readLine3);
		l_read->M_Translate();
		M_AssertEqual<bool>("testing read line of code for bool :","bool",true,
			VarHT::M_Shared().m_hTableOfBool.M_FindVariable("f")->m_value);
	}
	void M_TestReadStr(void) const {
		std::string l_readLine4 = "read \"test4.txt\" i;";
		CLine::LineOfCode* l_read = new CLine::LineOfCode_Read(l_readLine4);
		l_read->M_Translate();
		M_AssertEqual<std::string>("testing read line of code for string :","string","hello world",
			VarHT::M_Shared().m_hTableOfStr.M_FindVariable("i")->m_value);
	}
	void M_TestCondition(void) const {
		std::string l_cond = "[i] = [h]";
		Condition l_condObj(l_cond);
		l_condObj.M_Init();
		std::cout << "> testing condition '=' :\n	";
		std::cout << "	" << l_cond << " : " << l_condObj.M_Compare() << std::endl;
	}
	void M_TestForLoop(void) const {
		std::cout << "> testing for loop :\n";
		Vector<std::string> l_vecLineStr;
		l_vecLineStr.M_PushBack("set int foo = 0;");
		l_vecLineStr.M_PushBack("for [foo] < [5]+");
		l_vecLineStr.M_PushBack("begin");

		l_vecLineStr.M_PushBack("println foo;");

		l_vecLineStr.M_PushBack("end");
		Program l_program(l_vecLineStr);
		l_program.M_Execute();
		std::cout << "	for loop succeeded!!" << std::endl;
	}
}; 

#endif