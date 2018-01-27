#ifndef VERTEX_DATA_HEADER
#define VERTEX_DATA_HEADER

#include "../primitives/vertex.h"
#include "../primitives/tvertex.h"

struct VertexData
{
	Vertex* vData;
	unsigned int numVertices;
};

struct TexturedData
{
	TVertex* vData;
	unsigned int numVertices;
};

#endif