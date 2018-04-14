#ifndef MATRIX_HEADER
#define MATRIX_HEADER

#include <stdint.h>
#include <utility>

namespace glmath
{
	template<uint32_t _Dmx, uint32_t _Dmy, typename _Ty>
	class Matrix
	{
	public:
		Matrix(_Ty&& val)
		{
			for (uint32_t i = 0; i < _Dmy; ++i)
				m_c[i][i] = val;
		}
	private:
		// matrix grid
		_Ty m_c[_Dmx][_Dmy];
	};
}

#endif