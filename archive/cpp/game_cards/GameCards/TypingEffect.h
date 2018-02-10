#pragma once
#include <string>
using namespace std;

class TypingEffect
{
public:
	TypingEffect();
	~TypingEffect();
	static void effect(string text);
	static void countDown(string text);
};

