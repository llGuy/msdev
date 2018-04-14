#include "Simplify.h"
#include <math.h>



Simplify::Simplify(int numeratorInput, int denominatorInput)
{
	this->numerator = numeratorInput;
	this->denominator = denominatorInput;
}
int Simplify::simpFrac()
{
	bool frac = true;
	while (frac)
	{
		frac = false;
		for (int i = 2; i <= fabs(this->numerator); i++)
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


Simplify::~Simplify()
{
}
