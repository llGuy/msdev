#ifndef MISC_HEADER
#define MISC_HEADER

#include <iostream>

template<typename T>
void Log(T t)
{
	std::cout << "LOG> " << t << std::endl;
}

template<typename P1, typename ... Args>
void Log(P1 first, Args... otherParams)
{
	std::cout << "LOG> " << first << std::endl;
	Log(otherParams...);
}

#endif