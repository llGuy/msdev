#ifndef VECTOR_OUTPUT_HEADER
#define VECTOR_OUTPUT_HEADER

#include <algorithm>
#include <iostream>
#include <iterator>
#include "vector.h"
#include "matrix.h"

template<typename _Ty, uint32_t _Dm>
std::ostream& operator<<(std::ostream& os, vec<_Ty, _Dm>& v)
{
  std::copy(v.Begin(), v.End(), std::ostream_iterator<_Ty>(os, " "));
  return os;
}

template<typename _Ty, uint32_t _Dm>
std::ostream& operator<<(std::ostream& os, matrix<_Ty, _Dm>& m)
{
  uint32_t index = 0;
  std::for_each(m.Begin(), m.End(), [&](_Ty& v) { os << v << ((index++) % _Dm == _Dm - 1 ? "\n" : " "); });
  return os;
}

#endif
