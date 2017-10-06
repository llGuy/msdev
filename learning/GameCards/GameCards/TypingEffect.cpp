#include "TypingEffect.h"
#include <string>
#include <iostream>
#include <Windows.h>
using namespace std;

TypingEffect::TypingEffect()
{
}
void TypingEffect::effect(string text)
{
	int x = 0;
	while (text[x] != '\0')
	{
		cout << text[x];
		Sleep(rand() % 25 + 25);
		x++;
	}
	Sleep(1000);
}
void TypingEffect::countDown(string text)
{
	int x = 0;
	while (text[x] != '\0')
	{
		cout << text[x] << endl;
		Sleep(1000);
		x++;
	};
}

TypingEffect::~TypingEffect()
{
}
