#include "Function.h"



Function::Function(int InputNumerator, int InputDenominator)
{
	this->numerator = InputNumerator;
	this->denominator = InputDenominator;
}
int Function::conversion()
{
	int decimal = (1 / denominator) * numerator;
	return 0;
}


Function::~Function()
{
}
