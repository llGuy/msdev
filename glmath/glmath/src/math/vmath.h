#ifndef VMATH_HEADER
#define VMATH_HEADER
#include <math.h>
#include "vec/vec.h"

namespace glmath
{
	__forceinline
	Vector3f Normalize(Vector3f& v)
	{
		return v / v.Length();
	}
	__forceinline
	float Dot(Vector3f& v1, Vector3f& v2)
	{
		float res = 0.0f;
		for (uint32_t i = 0; i < 3; ++i) res += v1[i] * v2[i];
		return res;
	}
	__forceinline
	Vector3f Cross(Vector3f& v1, Vector3f& v2)
	{
		Vector3f res;
		uint32_t c = 1;
		for (; c <= 3; ++c)
		{
			res[c - 1] = v1[c % 3] * v2[(c + 1) % 3] - v1[(c + 1) % 3] * v2[c % 3];
		}
		return res;
	}
}

#endif