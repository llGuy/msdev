#pragma once

#include "vector.h"

template<typename _Ty, uint32_t _Dm>
vec<_Ty, _Dm> Normalize(vec<_Ty, _Dm>& vector)
{
  return vector / vector.Length();
}

template<typename _Ty>
vec3<_Ty> Cross(vec3<_Ty>& v1, vec3<_Ty>& v2)
{
  vec3<_Ty> result;
  for(uint32_t c = 1; c <= 3; ++c)
  {
    result[c - 1] = v1[c % 3] * v2[(c + 1) % 3] - v1[(c + 1) % 3] * v2[c % 3];
  }
  return result;
}

template<typename _Ty>
_Ty Dot(vec3<_Ty>& v1, vec3<_Ty>& v2)
{
  _Ty result = static_cast<_Ty>(0);
  for(uint32_t i = 0; i < 3; ++i) result += v1[i] * v2[i];
  return result;
}
