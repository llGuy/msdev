#ifndef TVERTEX_HEADER
#define TVERTEX_HEADER

#include <iostream>
#include <glm/glm.hpp>

struct TVertex
{
	/* world position */
	glm::vec3 wpos;
};

struct VData
{
	/* ptr to the data */
	TVertex* wposData;
	unsigned int numwpos;
};

#endif