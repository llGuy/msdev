#ifndef IO_HEADER	
#define IO_HEADER

#include "../string.h"

// IO
std::ostream& operator<<(std::ostream& os, String& s)
{
	const char* cs = s.C_Str();
	for (String::size_type i = 0; i <= s.Size(); ++i)
		os << cs[i];
	return os;
}

#endif