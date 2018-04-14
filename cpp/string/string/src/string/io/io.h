#ifndef IO_HEADER	
#define IO_HEADER

#include "../string.h"

// IO
std::ostream& operator<<(std::ostream& os, ltd::string& s)
{
	const char* cs = s.c_str();
	for (ltd::string::size_type i = 0; i <= s.size(); ++i)
		os << cs[i];
	return os;
}

#endif