#include "string/string.h"
#include "string/io/io.h"

#include <chrono>

void AccessTest(ltd::string& s)
{
	const char* cs = s.c_str();
}

double RunSSOTest(void)
{
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	for (unsigned int i = 0; i < 0xffff; ++i)
	{
		ltd::string s = "hi";
	}
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::duration d = end - start;
	double count = d.count();
	return count ;
}

double RunHeapTest(void)
{
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	for (unsigned int i = 0; i < 0xffff; ++i)
	{
		ltd::string s = "asdfasdfasdfasdfasdfasdf";
	}
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::duration d = end - start;
	double count = d.count();
	return count;
}

int main(void)
{
	ltd::string s = "hello world";
	double s1 = RunSSOTest();
	double s2 = RunHeapTest();

	std::cout << "\n\n" << s1 << std::endl << s2 << std::endl;
	std::cin.get();
}