#include "MyClass.h"

using namespace std;

bool MyClass::enable_debug = true;

MyClass::MyClass() : MyClass(-1)
{
	// calls the MyClass(-1) constructor above
}

MyClass::MyClass(int64_t value)
{
	this->value = value;
	DebugInfo("   constructor");
}


MyClass::~MyClass()
{
	DebugInfo("   destructor");
	value = -1;
}

void MyClass::Prime(int64_t number)
{
	DebugInfo("Prime:" + std::to_string(number));
}

void MyClass::Factoral(int64_t number)
{
	DebugInfo("Factoral:" + std::to_string(number));
}


void MyClass::DebugInfo(string title)
{
	if (enable_debug) {
		cout << title << " value:" << value << " address:" << this << endl;
	}
}