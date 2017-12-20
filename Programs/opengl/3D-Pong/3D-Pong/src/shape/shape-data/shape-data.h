#ifndef SHAPE_DATA_HEADER
#define SHAPE_DATA_HEADER

#include "..\..\vertex.h"

#include <GL\glew.h>

struct ShapeData
{
	Vertex* m_vertices;
	GLuint m_numVertices;
	GLushort* m_indices;
	GLuint m_numIndices;
public:
	explicit ShapeData()
		: m_vertices(0), m_numVertices(0), m_indices(0), m_numIndices(0)
	{
	}
	~ShapeData(void)
	{
		//DeleteAll();
	}
	GLsizeiptr vertexBufferSize() const
	{
		return m_numVertices * sizeof(Vertex);
	}

	GLsizeiptr indexBufferSize(void) const
	{
		return m_numIndices * sizeof(GLushort);
	}
private:
	void DeleteAll(void)
	{
		delete[] m_vertices;
		delete[] m_indices;
		m_numVertices = m_numIndices = 0;
	}
};

#endif