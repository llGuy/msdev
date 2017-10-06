#pragma once
#include "CodeLine.h"
#include "Condition.h"
#include "Program.h"
#include <string>
class Test {
public:
	explicit Test(void) {};
	~Test(void) {};
	void Run(void) {
		/*
		//constant initialization
		TestConstantIntInit();
		TestConstantCharInit();
		TestConstantBoolInit();
		TestConstantStringInit();
		//variable initialization
		TestVariableIntInit();
		TestVariableCharInit();
		TestVariableBoolInit();
		TestVariableStringInit();
		//operation initialization
		TestOperationInit();
		//constant modification
		TestConstantIntMod();
		TestConstantCharMod();
		TestConstantBoolMod();
		TestConstantStringMod();
		//variable modification
		TestVariableIntMod();
		TestVariableCharMod();
		//operation modification
		TestOperationMod();
		//print statement
		TestPrintState();
		//input statement
			//TestInputState();
		//condition
		TestCondition();
		//test program
		TestProgram();
		//testing program with ifs
		TestProgramWithIf();
		//testing program with fors
		TestProgramWithFor();
		//testing program with whiles
		TestProgramWithWhile();
		//testing modulo operator
		TestModuloOperator();
		//testing println
		TestPrintln();
		//testing saving to files
		//TestSave();
		*/
		TestIfAndElse();
	}
private:
	template<class T> void AssertEqual(const char* comment, const char* typeStr, T t1, T t2) const {
		std::cout << "> " << comment << " : ";
		std::string _ult = t1 == t2 ? "true" : "false";
		std::cout << _ult << std::endl;
		std::cout << "  " << typeStr << " 1 = " << t1 << " | " << typeStr << " 2 = " << t2 << std::endl;
	}
	void TestConstantIntInit(void) {
		CLine::LineOfCode* _line1;
		_line1 = new CLine::SetLineOfCode("set int a = 42;");
		_line1->TranslateToCPP();
		AssertEqual<int>("testing constant int initialization", "int", 42, 
			VList::listInt.FindNodeStr("a",VList::listInt._head)->_value);
		CLine::LineOfCode* _line2;
		_line2 = new CLine::SetLineOfCode("set int b = 43;");
		_line2->TranslateToCPP();
		AssertEqual<int>("testing 2nd constant int initialization", "int", 43, 
			VList::listInt.FindNodeStr("b",VList::listInt._head)->_value);
		std::cout << std::endl;
	}
	void TestConstantCharInit(void) {
		CLine::LineOfCode* _line1;
		_line1 = new CLine::SetLineOfCode("set char c = 'a';");
		_line1->TranslateToCPP();
		AssertEqual<char>("testing constant char initialization","char",'a',
			VList::listChar.FindNodeStr("c",VList::listChar._head)->_value);
		CLine::LineOfCode* _line2;
		_line2 = new CLine::SetLineOfCode("set char d = 'b';");
		_line2->TranslateToCPP();
		AssertEqual<char>("testing constant char initialization","char",'b',
			VList::listChar.FindNodeStr("d",VList::listChar._head)->_value);
		std::cout << std::endl;
	}
	void TestConstantBoolInit(void) {
		CLine::LineOfCode* _line1;
		_line1 = new CLine::SetLineOfCode("set bool e = true;");
		_line1->TranslateToCPP();
		AssertEqual<bool>("testing constant bool initialization","bool",true,
			VList::listBool.FindNodeStr("e",VList::listBool._head)->_value);
		CLine::LineOfCode* _line2;
		_line2 = new CLine::SetLineOfCode("set bool f = false;");
		_line2->TranslateToCPP();
		AssertEqual<bool>("testing constant bool initialization","bool",false,
			VList::listBool.FindNodeStr("f",VList::listBool._head)->_value);
		std::cout << std::endl;
	}
	void TestConstantStringInit(void) {
		CLine::LineOfCode* _line1;
		_line1 = new CLine::SetLineOfCode("set string g = \"foo\";");
		_line1->TranslateToCPP();
		AssertEqual<std::string>("testing constant string initialization","string","foo",
			VList::listStr.FindNodeStr("g",VList::listStr._head)->_value);
		CLine::LineOfCode* _line2;
		_line2 = new CLine::SetLineOfCode("set string h = \"bar\";");
		_line2->TranslateToCPP();
		AssertEqual<std::string>("testing constant string initialization","string","bar",
			VList::listStr.FindNodeStr("h",VList::listStr._head)->_value);
		std::cout << std::endl << std::endl;
	}
	void TestVariableIntInit(void) {
		CLine::LineOfCode* _line1;
		_line1 = new CLine::SetLineOfCode("set int i = a;");
		_line1->TranslateToCPP();
		AssertEqual<int>("testing variable int initialization","int",42,
			VList::listInt.FindNodeStr("i",VList::listInt._head)->_value);
		std::cout << std::endl;
	}
	void TestVariableCharInit(void) {
		CLine::LineOfCode* _line1;
		_line1 = new CLine::SetLineOfCode("set char j = c;");
		_line1->TranslateToCPP();
		AssertEqual<char>("testing variable char initialization","char",'a',
			VList::listChar.FindNodeStr("j",VList::listChar._head)->_value);
		std::cout << std::endl;
	}
	void TestVariableBoolInit(void) {
		CLine::LineOfCode* _line1;
		_line1 = new CLine::SetLineOfCode("set bool k = e;");
		_line1->TranslateToCPP();
		AssertEqual<bool>("testing variable bool initialization","bool",true,
			VList::listBool.FindNodeStr("k",VList::listBool._head)->_value);
		std::cout << std::endl;
	}
	void TestVariableStringInit(void) {
		CLine::LineOfCode* _line1;
		_line1 = new CLine::SetLineOfCode("set string l = g;");
		_line1->TranslateToCPP();
		AssertEqual<std::string>("testing variable string initialization","string","foo",
			VList::listStr.FindNodeStr("l",VList::listStr._head)->_value);
		std::cout << std::endl << std::endl;
	}
	void TestOperationInit(void) {
		CLine::LineOfCode* _line1;
		_line1 = new CLine::SetLineOfCode("set int m = 12 + 2 * (3 + 4) - 1;");
		_line1->TranslateToCPP();
		AssertEqual<int>("testing operation int initialization","int",12 + 2 * (3 + 4) - 1,
			VList::listInt.FindNodeStr("m",VList::listInt._head)->_value);
		CLine::LineOfCode* _line2;
		_line2 = new CLine::SetLineOfCode("set int n = (m + 2) / (3 + 6);");
		_line2->TranslateToCPP();
		AssertEqual<int>("testing operation int initialization","int",3,
			VList::listInt.FindNodeStr("n",VList::listInt._head)->_value);
		std::cout << std::endl << std::endl;
	}
	void TestConstantIntMod(void) {
		CLine::LineOfCode* _line1;
		_line1 = new CLine::ModLineOfCode("mod m -> 10;");
		_line1->TranslateToCPP();
		AssertEqual<int>("testing constant int modification","int",10,
			VList::listInt.FindNodeStr("m",VList::listInt._head)->_value);
		std::cout << std::endl;
	}
	void TestConstantCharMod(void) {
		CLine::LineOfCode* _line1;
		_line1 = new CLine::ModLineOfCode("mod c -> 'b';");
		_line1->TranslateToCPP();
		AssertEqual<char>("testing constant char modification","char",'b',
			VList::listChar.FindNodeStr("c",VList::listChar._head)->_value);
		std::cout << std::endl;
	}
	void TestConstantBoolMod(void) {
		CLine::LineOfCode* _line1;
		_line1 = new CLine::ModLineOfCode("mod e -> false;");
		_line1->TranslateToCPP();
		AssertEqual<bool>("testing constant bool modification","bool",false,
			VList::listBool.FindNodeStr("e",VList::listBool._head)->_value);
		std::cout << std::endl;
	}
	void TestConstantStringMod(void) {
		CLine::LineOfCode* _line1;
		_line1 = new CLine::ModLineOfCode("mod l -> \"hello world\";");
		_line1->TranslateToCPP();
		AssertEqual<std::string>("testing constant string modification","string","hello world",
			VList::listStr.FindNodeStr("l",VList::listStr._head)->_value);
		std::cout << std::endl << std::endl;
	}
	void TestVariableIntMod(void) {
		CLine::LineOfCode* _line1;
		_line1 = new CLine::ModLineOfCode("mod a -> b;");
		_line1->TranslateToCPP();
		AssertEqual<int>("testing variable int modification","int",43,
			VList::listInt.FindNodeStr("a",VList::listInt._head)->_value);
		std::cout << std::endl;
	}
	void TestVariableCharMod(void) {
		CLine::LineOfCode* _line1;
		_line1 = new CLine::ModLineOfCode("mod c -> d;");
		_line1->TranslateToCPP();
		AssertEqual<char>("testing variable char modification","char",'b',
			VList::listChar.FindNodeStr("c",VList::listChar._head)->_value);
		std::cout << std::endl << std::endl;
	}
	void TestOperationMod(void) {
		CLine::LineOfCode* _line1;
		_line1 = new CLine::ModLineOfCode("mod a -> 12 + 3 * (4 - 1) + 1;");
		_line1->TranslateToCPP();
		AssertEqual<int>("testing operation modification","int",22,
			VList::listInt.FindNodeStr("a",VList::listInt._head)->_value);
		CLine::LineOfCode* _line2;
		_line2 = new CLine::ModLineOfCode("mod a -> a + 1;");
		_line2->TranslateToCPP();
		AssertEqual<int>("testing operation modification","int",23,
			VList::listInt.FindNodeStr("a",VList::listInt._head)->_value);
		CLine::LineOfCode* _line3;
		_line3 = new CLine::ModLineOfCode("mod a -> (a - 3) / (2 + 3);");
		_line3->TranslateToCPP();
		AssertEqual<int>("testing operation modification","int",4,
			VList::listInt.FindNodeStr("a",VList::listInt._head)->_value);
		std::cout << std::endl << std::endl;
	}
	void TestPrintState(void) {
		std::cout << "testing print statement : ";
		CLine::LineOfCode* _line1;
		_line1 = new CLine::PrintLineOfCode("print a;");
		_line1->TranslateToCPP();
		std::cout << std::endl << std::endl;
	}
	void TestInputState(void) {
		std::cout << "testing input statement : ";
		CLine::LineOfCode* _line1;
		_line1 = new CLine::InputLineOfCode("input a;");
		_line1->TranslateToCPP();
		std::cout << VList::listInt.FindNodeStr("a",VList::listInt._head)->_value << std::endl;
		std::cout << std::endl << std::endl;
	}
	void TestCondition(void) {
		std::cout << "testing condition : \n";
		Condition _condition1("[b] = [43]");
		_condition1.Init();
		bool _result = _condition1.Compare();
		AssertEqual<bool>("testing condition","bool",true,_result);
		std::cout << std::endl;
	}
	void TestProgram(void) {
		std::cout << "testing program : \n";
		Vector<std::string> _vec;
		_vec.PushBack("set int frst = 42;");
		_vec.PushBack("print frst;");
		_vec.PushBack("print \"\n\";");
		Program _program(_vec);
		_program.ExecuteProgram();
	}
	void TestProgramWithIf(void) {
		std::cout << "testing program with bodies : \n";
		Vector<std::string> _vec;
		_vec.PushBack("if [b] = [43]");
		_vec.PushBack("begin");
		_vec.PushBack("print \"i am in the if statement\n\";");
		_vec.PushBack("set int lol = b;");
		_vec.PushBack("if [b + 1] = [44]");
		_vec.PushBack("begin");
		_vec.PushBack("print \"if-ception\n\";");
		_vec.PushBack("end");

		_vec.PushBack("end");

		Program _program(_vec);
		_program.ExecuteProgram();
	}
	void TestProgramWithFor(void) {
		std::cout << "testing program with for loops : \n";

		Vector<std::string> _vec;
		_vec.PushBack("set int x = 0;");

		_vec.PushBack("for [x] < [5] +");
		_vec.PushBack("begin");

		_vec.PushBack("set int y = x;");

		_vec.PushBack("if [y] = [2]");
		_vec.PushBack("begin");

		_vec.PushBack("set int z = 0;");
		_vec.PushBack("for [z] < [3] +");
		_vec.PushBack("begin");
		_vec.PushBack("print y;");
		_vec.PushBack("end");
		
		_vec.PushBack("end");


		_vec.PushBack("print \"\n\";");
		_vec.PushBack("end");

		_vec.PushBack("print \"hello world\n\";");
		_vec.PushBack("print \"yo\n\";");
		
		Program _program(_vec);
		_program.ExecuteProgram();
	}
	void TestProgramWithWhile(void) {
		std::cout << "testing program with while loops : \n";
		Vector<std::string> _vec;
		_vec.PushBack("set int qwerty = 0;");
		_vec.PushBack("while [qwerty] < [5]");
		_vec.PushBack("begin");
		_vec.PushBack("print \"hello world\n\";");
		_vec.PushBack("mod qwerty -> qwerty + 1;");
		_vec.PushBack("end");

		Program _program(_vec);
		_program.ExecuteProgram();
	}
	void TestModuloOperator(void) {
		std::cout << "testing modulo operator : \n";
		CLine::LineOfCode* _line = new CLine::SetLineOfCode("set int asdf = 9 % 3;");
		_line->TranslateToCPP();
		AssertEqual<int>("testing operation int initialization","int",9 % 3,
			VList::listInt.FindNodeStr("asdf",VList::listInt._head)->_value);
	}
	void TestPrintln(void) {
		std::cout << "testing println : \n";
		CLine::LineOfCode* _line = new CLine::PrintlnLineOfCode("println \"hello world\";");
		_line->TranslateToCPP();
	}
	void TestSave(void) {
		std::cout << "testing save : \n";
		CLine::LineOfCode* _line = new CLine::SaveLineOfCode("save \"C:\\Users\\luc\\Desktop\\program.txt\" a;");
		_line->TranslateToCPP();
	}
	void TestEncryption(void) {
		std::cout << "testing XOR encryption : \n";
		Vector<std::string> _vec;
		_vec.PushBack("set string s = \"hello\";");
		_vec.PushBack("");
	}
	void TestIfAndElse(void) {
		std::cout << "testing if and elifs : "; 
		Vector<std::string> _vec;
		_vec.PushBack("println \"hi\";");
		_vec.PushBack("if [1] = [0]");
		_vec.PushBack("begin");
		_vec.PushBack("println \"hello world\";");
		_vec.PushBack("end");
		_vec.PushBack("else");
		_vec.PushBack("begin");
		_vec.PushBack("println \"yo\";");
		_vec.PushBack("end");
		_vec.PushBack("endif");
		_vec.PushBack("println \"hi\";");
		Program _program(_vec);
		_program.ExecuteProgram();
	}
};