#include "Typing.h"
#include <iostream>
#include <Windows.h>
using namespace std;
Typing::Typing()
{
}
void Typing::effect(string text)
{
	int x = 0;
	while (text[x] != '\0')
	{
		cout << text[x];
		Sleep(rand() % 25 + 25);
		x++;
	};
}

Typing::~Typing()
{
}
