#include "type_test.h"

TypingTest::TypingTest(const char* directory)
{
  ParseFile(directory);
}

void TypingTest::RunTest(void)
{
  double time = 0.0;
  int32_t w = 0;
  while(w < m_words.size() - 1)
  {
    std::string word;
    std::cout << m_words[w] << " " << m_words[w + 1] << "\r";
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::cin >> word;
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    time += (double)((end - start).count() / 1000000000.0);
    if(word != m_words[w])
    {
      std::cout << "typo" << "\n\n";
    }
    else
    {
      w++;
      //      std::cout << "success : " << WordsPerMinute() << "\n\n";
      m_avTime += time;
      std::cout << time << "s \n\n";
      time = 0.0;
    }
  }
  m_avTime /= static_cast<double>(m_words.size());
    // std::cout << m_avTime<< std::endl;
}

int32_t TypingTest::WordsPerMinute(void)
{
  return static_cast<int32_t>(60.0 / m_avTime);
}

void TypingTest::ParseFile(const char* directory)
{
  std::fstream file(directory);
  while(file)
  {
    std::string word;
    file >> word;
    m_words.push_back(word);
  }
  std::cout << "number of words : " << m_words.size() << std::endl;
}
