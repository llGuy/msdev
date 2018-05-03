#include "myadd.h"
#include "helper.h"

#include <iostream>
#include <vector>

struct MyStruct
{
  int a;
  int b;
};

int main()
{
  MyAdd addObj;
  Helper h;

  MyStruct s;

  std::vector<int> vector;
  
  std::cout << "addition result: " << addObj.add(1, 1) << "\n";
}
