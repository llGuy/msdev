#pragma once
#include <iostream>

using namespace std;
class Bisection
{
public:
	Bisection(double _inputx0, double _inputx1);
	~Bisection();
	double solve(double x0 , double x1);
	double initialFunction(double x);
private:
	double _x0;
	double _x1;
	double _middles;
};

