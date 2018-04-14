#pragma once
#include "CodeLine.h"
#include "CalcParsing.h"
#include <string>
class CompilerTests {
public:
	static void Run() {
		CompilerTests test;
		test.TestSetInitializeInt();
		test.TestSetInitializeChar();
		test.TestSetInitializeStr();
		test.TestSetInitializeBool();
		test.TestSetInitializedVar();
		test.TestSetInitializedOperation();
		test.TestParser();
	}

	void AssertTrue(bool value, std::string comment = "") {
		if(!value) {
			std::cout << "test failed " << comment << std::endl;
		}
		else {
			std::cout << "test succeeded " << comment << std::endl;
		}
	}
	void AssertEqual(int v1, int v2, std::string comment = "") {
		if(v1 != v2) {
			std::cout << "test failed " << v1 << "!=" << v2 << comment << std::endl;
		}
		else {
			std::cout << "test succeeded " << comment << std::endl;
			std::cout << v1 << " = " << v2 << std::endl << std::endl;
		}
	}
	void AssertEqualChar(char c1,char c2,std::string comment = "") {
		if(c1 != c2) {
			std::cout << "test failed " << c1 << "!=" << c2 << comment << std::endl;
		}
		else {
			std::cout << "test succeeded " << comment << std::endl;
			std::cout << c1 << " = " << c2 << std::endl << std::endl;
 		}
	}
	void AssertEqualString(std::string s1, std::string s2, std::string comment = "") {
		if(s1 != s2) std::cout << "test failed " << s1 << "!=" << s2 << comment << std::endl;
		else {
			std::cout << "test succeeded " << comment << std::endl;
			std::cout << s1 << " = " << s2 << std::endl << std::endl;
		}
	}
	void AssertEqualBool(bool b1, bool b2, std::string comment) {
		if(b1 != b2) std::cout << "test failed " << b1 << "!=" << b2 << comment << std::endl;
		else {
			std::cout << "test succeeded " << comment << std::endl;
			std::cout << b1 << " = " << b2 << std::endl << std::endl;
		}
	}

	void TestSetInitializeInt() {
		std::cout << "testing int initialization\n";
		CLine::CodeLine * line = new CLine::SCLInitialize("set int foo = 133;");
		line->TranslateToCPP();

		AssertTrue(VList::listInt._numOfInitializedVar == 1, "double variable initialized");
		AssertEqual(VList::listInt.FindNodeStr("foo",VList::listInt._head)->_value, 133, "basic initialization");

		CLine::CodeLine * line2 = new CLine::SCLInitialize("set int fee = 4242;");
		line2->TranslateToCPP();

		AssertEqual(VList::listInt.FindNodeStr("fee",VList::listInt._head)->_value, 4242, "basic initialization");
	}
	void TestSetInitializeChar() {
		std::cout << "testing char initialization\n";
		CLine::CodeLine * line = new CLine::SCLInitialize("set char frr = 'a';");
		line->TranslateToCPP();

		AssertTrue(VList::listChar._numOfInitializedVar == 1,"one variable initialized");
		AssertEqualChar(VList::listChar.FindNodeStr("frr", VList::listChar._head)->_value, 'a',"basic initialization");
	}
	void TestSetInitializeStr() {
		std::cout << "testing string initialization\n";
		CLine::CodeLine * line = new CLine::SCLInitialize("set string str = \"hello world\";");
		
		line->TranslateToCPP();
		AssertEqualString(VList::listStr.FindNodeStr("str", VList::listStr._head)->_value, "hello world", "basic initialization");
	}
	void TestSetInitializeBool() {
		std::cout << "testing bool initialization\n";
		CLine::CodeLine * line = new CLine::SCLInitialize("set bool fa = false;");

		line->TranslateToCPP();
		AssertEqualBool(VList::listBool.FindNodeStr("fa", VList::listBool._head)->_value, false,"basic bool initialization");
	}
	void TestSetInitializedVar() {
		std::cout << "testing variable initialization\n";
		CLine::CodeLine * line = new CLine::SCLInitialize("set int ba = 7;");
		line->TranslateToCPP();
		std::cout << "created first int\n";

		CLine::CodeLine * line2 = new CLine::SCLInitialize("set int be = ba;");
		line2->TranslateToCPP();
		std::cout << "created second int\n";

		AssertEqual(VList::listInt.FindNodeStr("be", VList::listInt._head)->_value, VList::listInt.FindNodeStr("ba", VList::listInt._head)->_value, "variable");
	}
	void TestSetInitializedOperation() {
		std::cout << "testing operation initialization\n";
		CLine::CodeLine * line = new CLine::SCLInitialize("set int lol = (90 - 9) / (2 + ba);");
		line->TranslateToCPP();
		AssertEqual(VList::listInt.FindNodeStr("lol",VList::listInt._head)->_value, 9, "operation");
	}
	void TestParser() {
		std::cout << "\n\ntesting the parser\n";
		std::string exp[] = {"12 * (3 + 2) / 3 + 1","(90 - 9) / (2 + ba)","2 * (1 + 3 * (2 + 2)) + 1"};
		double res[] ={ 12 * (3 + 2) / 3 + 1, (90-9)/(2+7), 2 * (1 + 3 * (2 + 2)) + 1 };
		CalcParser parser1;
		parser1._expression = exp[0];
		std::cout << exp[0] << " = " << parser1.Calculate() << " actual answer : " << res[0] <<std::endl;

		CalcParser parser2;
		parser2._expression = exp[1];
		std::cout << exp[1] << " = " << parser2.Calculate() << " actual answer : "  << res[1] << std::endl;

		CalcParser parser3;
		parser3._expression = exp[2];
		std::cout << exp[2] << " = " << parser3.Calculate() <<  " actual answer : " << res[2] << std::endl;
	}
};