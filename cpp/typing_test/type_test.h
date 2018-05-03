#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class TypingTest
{
public:
  // typing test will read from a file with random words
  TypingTest(const char* directory);
  ~TypingTest(void) = default;

  void RunTest(void);

  int32_t WordsPerMinute(void);
private:
  void ParseFile(const char* directory);  
private:
  std::vector<std::string> m_words;
  double m_avTime;
};
