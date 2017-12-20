#ifndef SHAPE_HEADER
#define SHAPE_HEADER

#include <glm\glm.hpp>
#include <GL\glew.h>

class Shape
{
protected:
	virtual ~Shape(void)
	{
	}
public:
	virtual void Draw(glm::mat4 viewProjectionMatrix) 
	{
	}
protected:
	void CreateBuffer(unsigned int* bufferID, unsigned int size, glm::vec3* verts)
	{
		glGenBuffers(1, bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, *bufferID);
		glBufferData(GL_ARRAY_BUFFER, size, verts, GL_STATIC_DRAW);
	}
	void CreateVertexArrayObject(unsigned int* vaoID, unsigned int* bufferID)
	{
		glGenVertexArrays(1, vaoID);
		glBindVertexArray(*vaoID);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, *bufferID);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));
	}
	void CreateIndexBuffer(unsigned int* indexBufferID, unsigned int size, unsigned short* indices)
	{
		glGenBuffers(1, indexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}
protected:
	unsigned int m_bufferID;
	unsigned int m_indexBufferID;
	unsigned int m_vertexArrayObjectID;

	glm::vec3* m_vertices;
	//unsigned short* m_indices;

	unsigned int m_numIndices;
	unsigned int m_numVertices;
};

#endif