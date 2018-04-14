#ifndef MATH_HEADER
#define MATH_HEADER

#include <math.h>
#include "vec/vec.h"

namespace glmath
{
	float Sqrt(const float& f)
	{
		static constexpr uint32_t PRECISION = 17;

		uint32_t loop = 0;
		float res = 1.0f;
		float diff = 1.0f;
		for (; loop < PRECISION;)
		{
			if (fabs(res * res - f) < 0.0001f) return res;
			else if (res * res < f) res += diff;
			else
			{
				diff /= 2.0f;
				res -= diff;
				++loop;
			}
		}
		return res;
	}
}

#endif