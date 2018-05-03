#include <iostream>
#include <math.h>

#define NEW_LINE '\n'

struct vector
{
    float x, y;
};

namespace proxy
{

    struct distance
    {
	distance(const vector& pos1, const vector& pos2)
	    : m_DistanceSquared((pos2.x - pos1.x) * (pos2.x - pos1.x) + (pos2.y - pos1.y) * (pos2.y - pos2.y))
	{
	}
	operator float(void) const
	{
	    return std::sqrt(m_DistanceSquared);
	}
	bool operator<(float d) const
	{
	    return m_DistanceSquared < d * d;
	}
	bool operator>(float d) const
	{
	    return m_DistanceSquared > d * d;
	}
	bool operator==(float d) const
	{
	    return fabs();
	}
    private:
	float m_DistanceSquared;
    };
    
}

int main(int argc, char** argv)
{
    using namespace proxy;
    
    vector v1{ 2.0f, 3.0f };
    vector v2{ 3.0f, 3.0f };

    distance d{ v1, v2 };

    std::cout << (float)d << NEW_LINE;
    
    return 0;
}
