#include <iostream>
#include "vec.h"

template<typename _Valty, uint32_t _Size>
class Vector
{
public:
  template<typename... _Val>
  Vector(_Val&&... values)
  {
    _Valty values[] { 0, values... };
    for(uint32_t i = 0; (i < _Size && (i < sizeof(values) / sizeof(_Valty)); ++i)
      {
	m_components[i] = values[i + 1];
      }
  }
  _Valty& operator[](const uint32_t index)
  {
     assert(index < _Size);
     return m_components[index];
  }
private:
  _Valty m_components[_Size];
};

int main(int argc, char* argv[])
{
  std::cout << "hello world" << "\n";

  Vector<float, 3> vec{3.0f, 2.0f, 1.0f};
  
  
  std::cin.get();
}
