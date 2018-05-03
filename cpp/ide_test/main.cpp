#include <iostream>
#include "helper.h"
#include "my_add.h"

int main()
{
  MyAdd add_obj;
  Helper h;

  std::cout << "addition result:" << add_obj.add(1,1) << '\n';
}
