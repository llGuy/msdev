#include "algorithm.h"

std::string CopyBefore(const std::string& s, char delimiter)
{
    std::string sub;
    for(auto& iter : s)
    {
	if(iter == delimiter) return sub;
	else sub.push_back(iter);
    }
    return s;
}

