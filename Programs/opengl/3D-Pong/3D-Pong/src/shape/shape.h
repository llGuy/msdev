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
	void CreateBuffer(unsigned int size, void* data)
	{
		glGenBuffers(1, &m_bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	void CreateIndexBuffer(unsigned int size, void* data)
	{
		glGenBuffers(1, &m_indexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	void CreateVertexBufferObject(void)
	{
		glGenVertexArrays(1, &m_vertexArrayObjectID);	
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayObjectID);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (float*)(3 * sizeof(float)));
	}
protected:
	unsigned int m_bufferID;
	unsigned int m_indexBufferID;
	unsigned int m_vertexArrayObjectID;

	glm::vec3* m_vertices;
	unsigned short* m_indices;

	unsigned int m_numIndices;
	unsigned int m_numVertices;
};

#endif