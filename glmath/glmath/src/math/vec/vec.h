#ifndef VEC_HEADER
#define VEC_HEADER

#include <stdint.h>
#include <utility>

#include "../math.h"

namespace glmath
{
	template<uint32_t _Dm, typename _Ty>
	class Vector
	{
	public:
		Vector(void) = default;
		template<typename... _Args>
		Vector(_Args&&... c)
		{
			const uint32_t size = 1 + sizeof...(c);
			_Ty arr[size] = {static_cast<_Ty>(0), c...};
			for (uint32_t i = 0; i < _Dm; ++i)
				m_c[i] = arr[i + 1];
		}

		// accessing the components of the vector
		__forceinline
		float& operator[](const uint32_t& i)
		{
			return m_c[i];
		}
		__forceinline
		Vector<_Dm, _Ty>&& operator*(const float& f)
		{
			Vector<_Dm, _Ty> v;
			for (uint32_t i = 0; i < _Dm; ++i) v.m_c[i] = f * m_c[i];
			return std::move(v);
		}
		Vector<_Dm, _Ty>&& operator/(const float& f)
		{
			Vector<_Dm, _Ty> v;
			for (uint32_t i = 0; i < 3; ++i) v.m_c[i] = m_c[i] / f;
			return std::move(v);
		}
		__forceinline
		_Ty Length(void)
		{
			_Ty result = static_cast<_Ty>(0);
			for (uint32_t i = 0; i < _Dm; ++i)
				result += m_c[i] * m_c[i];
			return Sqrt(result);
		}
	private:
		union
		{
			// components of the vector
			_Ty m_c[_Dm];
		};
	};
	using Vector3f = Vector<3, float>;
}

#endif