#ifndef LOG_HEADER
#define LOG_HEADER

#include <iostream>

template<typename P>
void Log(P p)
{
	std::cout << "LOG> " << p << std::endl;
}

template<typename P, typename... Args>
void Log(P p, Args... other)
{
	std::cout << "LOG> " << p << std::endl;
	Log(other...);
}

#endif