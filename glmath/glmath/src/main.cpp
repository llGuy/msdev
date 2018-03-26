#include "math/vec/vec.h"
#include "math/math.h"
#include "testing/test.h"

#include <iostream>

int main(void)
{
	glmath::Test crossdot(
		[=](float expected)->bool
		{
			glmath::Vec3 base1(1.0f, 0.0f, 0.0f);
			glmath::Vec3 base2(0.0f, 1.0f, 0.0f);
			glmath::Vec3 base3 = glmath::Cross(base1, base2);
			float perp = glmath::Dot(base3, base1);
			return fabs(expected - perp) < 0.0001f;
		},
		0.0f, "CROSS DOT PRODUCT TEST"
	);
	glmath::Test length(
		[=](float expected)->bool
		{
			glmath::Vec3 v(1.0f, 0.0f, 0.0f);
			return fabs(expected - glmath::Length(v)) < 0.0001f;
		},
		1.0f, "LENGTH TEST"
	);

	crossdot.RunTest();
	length.RunTest();

 	std::cin.get();
}