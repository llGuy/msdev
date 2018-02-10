#include "bisection.h"



Bisection::Bisection(double _inputx0,double _inputx1) {
	_x0 = _inputx0;
	_x1 = _inputx1;
	cout << "started process\n";
	solve(_x1,_x0);
}

Bisection::~Bisection() {

}

double Bisection::initialFunction(double x) {
	return x * x - 2;
}

double Bisection::solve(double x0,double x1) {
	while(_x1-_x0 > 1.0e-7) {
		//cout << _x0 << << initialFunction(_x0) << " " << initialFunction(_x1) << "\n\n";
		_middles = (_x1+_x0)/2;
		if(initialFunction(_middles) > 0) {
			_x1 = _middles;
		}
		else {
			_x0 = _middles;
		}
		printf("[%f,%f] -> %f,%f\n",_x0,_x1,initialFunction(_x0),initialFunction(_x1));
	}
	cout << "The real answer is " << sqrt(2);
	return 42;
}
