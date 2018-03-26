#ifndef VEC_HEADER
#define VEC_HEADER

#include <stdint.h>
#include <utility>

namespace glmath
{
	template<uint32_t _Dm>
	class Vec
	{
	public:
		Vec(void) = default;
		template<typename... _Args>
		Vec(_Args... c)
		{
			const uint32_t size = 1 + sizeof...(c);
			float arr[size] = {0.0f, c...};
			for (uint32_t i = 0; i < _Dm; ++i)
				c[i] = arr[i + 1];
		}

		// accessing the components of the vector
		__forceinline	
		float& operator[](const uint32_t& i)
		{
			return c[i];
		}
		__forceinline
		Vec<_Dm>&& operator*(const float& f)
		{
			Vec<_Dm> v;
			for (uint32_t i = 0; i < _Dm; ++i) v.c[i] = f * c[i];
			return std::move(v);
		}
		Vec<_Dm>&& operator/(const float& f)
		{
			Vec<_Dm> v;
			for (uint32_t i = 0; i < 3; ++i) v.c[i] = c[i] / f;
			return std::move(v);
		}
	public:
		union
		{
			float c[_Dm];
		};
	};

	template<>
	class Vec<3>
	{
	public:
		Vec(void) = default;
		Vec(float x, float y, float z)
			: x(x), y(y), z(z)
		{
		}
	public:
		// access
		__forceinline
		float& operator[](const uint32_t& i)
		{
			return c[i];
		}
		__forceinline
		Vec operator*(const float& f)
		{
			Vec<3> v;
			for (uint32_t i = 0; i < 3; ++i) v.c[i] = f * c[i];
			return v;
		}
		__forceinline
		Vec<3> operator/(const float& f)
		{
			Vec<3> v;
			for (uint32_t i = 0; i < 3; ++i) v.c[i] = c[i] / f;
			return v;
		}

		union
		{
			struct
			{
				float x, y, z;
			};
			float c[3];
		};
	};

	using Vec3 = Vec<3>;
}

#endif