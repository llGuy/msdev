#include "Fraction.h"



Fraction::Fraction(int inputNumerator, int inputDenomninator)
{
	this->numerator = inputNumerator;
	this->denominator = inputDenomninator;
}
int Fraction::simpFrac()
{
	bool frac = true;
	while (frac)
	{
		frac = false;
		for (int i = 2; i <= this->numerator; i++)
		{
			if (this->numerator % i == 0 && this->denominator % i == 0)
			{
				this->denominator = this->denominator / i;
				this->numerator = this->numerator / i;
				frac = true;
				break;
			}
		}
	}
	return 0;
}

Fraction::~Fraction()
{
}
