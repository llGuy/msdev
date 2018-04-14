#include "math/vec/vec.h"
#include "math/vmath.h"
#include "testing/test.h"

#include <iostream>

int main(void)
{
	glmath::Test crossdot(
		[=](float expected)->bool
		{
			glmath::Vector3f base1(1.0f, 0.0f, 0.0f);
			glmath::Vector3f base2(0.0f, 1.0f, 0.0f);
			glmath::Vector3f base3 = glmath::Cross(base1, base2);
			float perp = glmath::Dot(base3, base1);
			return fabs(expected - perp) < 0.0001f;
		},
		0.0f, "CROSS DOT PRODUCT TEST"
	);
	glmath::Test length(
		[=](float expected)->bool
		{
			glmath::Vector3f v(1.0f, 0.0f, 0.0f);
			return fabs(expected - v.Length()) < 0.0001f;
		},
		1.0f, "LENGTH TEST"
	);

	crossdot.RunTest();
	length.RunTest();

 	std::cin.get();
}