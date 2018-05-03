#include <type_traits>
#include <iostream>

template<bool ,typename T = void>
struct enable_if
{};

template<typename T>
struct enable_if<true, T>
{
  using type = T;
};

template<typename _Ty1, typename _Ty2>
auto divide(const typename enable_if<std::is_floating_point<_Ty1>::value, _Ty1>::type& d1,
	    const typename enable_if<std::is_floating_point<_Ty2>::value, _Ty2>::type& d2)
{
  return d1 / d2;
}

template<typename _Ty, typename enable_if<std::is_integral<_Ty>::value, _Ty>::type* = nullptr>
_Ty negate(_Ty t)
{
  return -t;
}

int main(void)
{
  std::cout << negate(2) << std::endl;
}
