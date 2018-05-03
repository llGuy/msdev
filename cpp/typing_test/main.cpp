#include <iostream>
#include "type_test.h"

int main(int argc, char* argv[])
{
  TypingTest test("test.txt");
  test.RunTest();
  std::cout << test.WordsPerMinute() << " words per minute" << std::endl;
  
  return 0;
}
