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

	__forceinline
	float Length(const Vec3& v)
	{
		return Sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}
	__forceinline
	Vec3 Normalize(Vec3& v)
	{
		return v / Length(v);
	}
	__forceinline
	float Dot(Vec3& v1, Vec3& v2)
	{
		float res = 0.0f;
		for (uint32_t i = 0; i < 3; ++i) res += v1[i] * v2[i];
		return res;
	}
	__forceinline 
	Vec3 Cross(Vec3& v1, Vec3& v2)
	{
		Vec3 res;
		uint32_t c = 1;
		for (; c <= 3; ++c)
		{
			res[c - 1] = v1[c % 3] * v2[(c + 1) % 3] - v1[(c + 1) % 3] * v2[c % 3];
		}
		return res;
	}
}

#endif