#include <iostream>
#include "Box.h"

using namespace std;

int main()
{
	Box Box1;	//Declare Box1
	Box Box2;	//Declare Box2
	double volume = 0.0;

	//Box1 specification
	Box1.height = 5.0;
	Box1.length = 6.0;
	Box1.breadth = 7.0;

	//Box2 specification
	Box2.height = 9.0;
	Box2.length = 8.0;
	Box2.breadth = 3.0;

	//Volume of Box1
	volume = Box1.height * Box1.length * Box1.breadth;
	cout << "Volume of Box1: " << volume << endl;

	//Volume of Box2
	volume = Box2.height * Box2.length * Box2.breadth;
	cout << "Volume of Box2: " << volume << endl;

	return 0;
}

double Box::getVolume(void)
{
	return length * breadth * height;
}