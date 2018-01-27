#ifndef CVEC2_HEADER
#define CVEC2_HEADER

#include <unordered_map>

struct CVec2
{
	unsigned char x, z;
};

struct WVec2
{
	signed int x, z;
	bool operator==(const WVec2& v) const
	{
		return (x == v.x && z == v.z);
	}
};

#endif