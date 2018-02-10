#include <iostream>
#include <string>
#include <Windows.h>
#include "Effect.h"

using namespace std;

int main()
{
	string text1 = "Hello World. My object works! \n\n";
	
	EffectSlow * slow = new EFfectSlow();
	Effect * fast = new Effect();
	int which;
	cin >> which;

	Effect * useEffect = NULL;
	if (which == 1) {
		useEffect = slow;
	}
	else {
		useEffect = fast;
	}

	useEffect->apply(text1);

	delete myEffect;
}