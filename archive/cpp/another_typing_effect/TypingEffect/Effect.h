#pragma once
#include <string>
#include <iostream>
using namespace std;

class Effect
{
public:
	Effect();
	~Effect();
	virtual void apply(string text);
};

class EffectSlow : Effect {
public:
	void apply(string text);
};
