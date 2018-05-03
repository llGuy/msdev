4#ifndef VECTOR_HEADER
#define VECTOR_HEADER

#include <new>
#include <array>
#include <type_traits>
#include "math.h"

template<typename _Ty, std::size_t _Dm>
struct vec
{
  using Type = _Ty;
  
  vec(void) = default;
  vec(const vec<_Ty, _Dm>& v)
  : m_Values(v.m_Values)
  {
  }
  
  template<typename... _T>
  vec(_Ty first, _T&&... args)
  : m_Values{first, args...}
  {
  }

  typename std::array<_Ty, _Dm>::iterator Begin()
  {
    return m_Values.begin();
  }
  typename std::array<_Ty, _Dm>::iterator End()
  {
    return m_Values.end();
  }
  
  inline
  _Ty& operator[](uint32_t sbscr)
  {
    return m_Values[sbscr];
  }
private:
  std::array<_Ty, _Dm> m_Values;
};

/*******************   3 DIMENSIONAL VECTOR    *********************/

template<typename _Ty>
struct vec<_Ty, 3>
{
  using Type = _Ty;
  
  vec(void) = default;
 vec(const vec<_Ty, 3>& v)
    : m_Values{v.m_Values}
  {
  }
  vec(_Ty a, _Ty b, _Ty c)
    : m_Values{a, b, c}
  {
  }

  typename std::array<_Ty, 3>::iterator Begin()
  {
    return m_Values.begin();
  }
  typename std::array<_Ty, 3>::iterator End()
  {
    return m_Values.end();
  }
  
  _Ty& operator[](uint32_t sbscr)
  {
    return m_Values[sbscr];
  }

  vec<_Ty, 3> operator*(_Ty value)
  {
    vec<_Ty, 3> newvector;
    for(uint32_t i = 0; i < 3; ++i)
      newvector[i] = value * m_Values[i];

    return newvector;
  }

  vec<_Ty, 3> operator/(_Ty value)
  {
    vec<_Ty, 3> newvector;
    for(uint32_t i = 0; i < 3; ++i)
      newvector[i] = m_Values[i] / value;

    return newvector;
  }

  _Ty Length(void)
  {
    _Ty total = static_cast<_Ty>(0);
    for(uint32_t i = 0; i < 3; ++i)
      total += m_Values[i] * m_Values[i];
    return SquareRoot(x * x + y * y + z * z);
  }

  union
  {
    struct { _Ty x, y, z; };
    struct { _Ty r, g, b; };
    std::array<_Ty, 3> m_Values;
  };
};

template<typename _Ty>
using vec3 = vec<_Ty, 3>;

#endif
