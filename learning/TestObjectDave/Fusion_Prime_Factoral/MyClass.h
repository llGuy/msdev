#pragma once
#include <iostream>
#include <string>

using namespace std;

class MyClass
{
public:
	static bool enable_debug;
	int64_t value;

	MyClass(int64_t value);
	MyClass();
	~MyClass();

	void Prime(int64_t number);
	void Factoral(int64_t number);

	void DebugInfo(string title);
};

