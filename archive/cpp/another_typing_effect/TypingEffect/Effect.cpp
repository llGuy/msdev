#include "Effect.h"
#include <string>
#include <iostream>
#include <Windows.h>

using namespace std;

Effect::Effect()
{
};

void Effect::apply(string text)
{
	int x = 0;
	while (text[x] != '\0')
	{
		cout << text[x];
		Sleep(rand() % 25 + 25);
		x++;
	};
}

Effect::~Effect()
{
};

void EffectSlow::apply(string text) {
	int x = 0;
	while (text[x] != '\0')
	{
		cout << text[x];
		Sleep(rand() % 100 + 100);
		x++;
	};

}