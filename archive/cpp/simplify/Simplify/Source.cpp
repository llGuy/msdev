#include <iostream>
#include <string>
#include "Fraction.h"

using namespace std;

int main()
{
	Fraction myFraction(8, 16);

	cout << myFraction.numerator << endl;
	cout << myFraction.denominator << endl;
	myFraction.simpFrac();
	cout << myFraction.numerator << endl;
	cout << myFraction.denominator << endl;
}

