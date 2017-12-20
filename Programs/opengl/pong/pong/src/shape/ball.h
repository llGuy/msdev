#ifndef BALL_HEADER
#define BALL_HEADER

#include "shape.h"

class Ball
	: public Shape
{
public:
	explicit Ball(void) //for the moment doesn't take ball direction vec3
	{
		glm::vec3 stackVerts[] = {
			glm::vec3(-1.0f, +1.0f, +1.0f), // 0
			glm::vec3(+1.0f, +0.0f, +0.0f), // Color
			glm::vec3(+1.0f, +1.0f, +1.0f), // 1
			glm::vec3(+0.0f, +1.0f, +0.0f), // Color
			glm::vec3(+1.0f, +1.0f, -1.0f), // 2
			glm::vec3(+0.0f, +0.0f, +1.0f), // Color
			glm::vec3(-1.0f, +1.0f, -1.0f), // 3
			glm::vec3(+1.0f, +1.0f, +1.0f), // Color
			
			glm::vec3(-1.0f, +1.0f, -1.0f), // 4
			glm::vec3(+1.0f, +0.0f, +1.0f), // Color
			glm::vec3(+1.0f, +1.0f, -1.0f), // 5
			glm::vec3(+0.0f, +0.5f, +0.2f), // Color
			glm::vec3(+1.0f, -1.0f, -1.0f), // 6
			glm::vec3(+0.8f, +0.6f, +0.4f), // Color
			glm::vec3(-1.0f, -1.0f, -1.0f), // 7
			glm::vec3(+0.3f, +1.0f, +0.5f), // Color
			
			glm::vec3(+1.0f, +1.0f, -1.0f), // 8
			glm::vec3(+0.2f, +0.5f, +0.2f), // Color
			glm::vec3(+1.0f, +1.0f, +1.0f), // 9
			glm::vec3(+0.9f, +0.3f, +0.7f), // Color
			glm::vec3(+1.0f, -1.0f, +1.0f), // 10
			glm::vec3(+0.3f, +0.7f, +0.5f), // Color
			glm::vec3(+1.0f, -1.0f, -1.0f), // 11
			glm::vec3(+0.5f, +0.7f, +0.5f), // Color
			
			glm::vec3(-1.0f, +1.0f, +1.0f), // 12
			glm::vec3(+0.7f, +0.8f, +0.2f), // Color
			glm::vec3(-1.0f, +1.0f, -1.0f), // 13
			glm::vec3(+0.5f, +0.7f, +0.3f), // Color
			glm::vec3(-1.0f, -1.0f, -1.0f), // 14
			glm::vec3(+0.4f, +0.7f, +0.7f), // Color
			glm::vec3(-1.0f, -1.0f, +1.0f), // 15
			glm::vec3(+0.2f, +0.5f, +1.0f), // Color
			
			glm::vec3(+1.0f, +1.0f, +1.0f), // 16
			glm::vec3(+0.6f, +1.0f, +0.7f), // Color
			glm::vec3(-1.0f, +1.0f, +1.0f), // 17
			glm::vec3(+0.6f, +0.4f, +0.8f), // Color
			glm::vec3(-1.0f, -1.0f, +1.0f), // 18
			glm::vec3(+0.2f, +0.8f, +0.7f), // Color
			glm::vec3(+1.0f, -1.0f, +1.0f), // 19
			glm::vec3(+0.2f, +0.7f, +1.0f), // Color
			
			glm::vec3(+1.0f, -1.0f, -1.0f), // 20
			glm::vec3(+0.8f, +0.3f, +0.7f), // Color
			glm::vec3(-1.0f, -1.0f, -1.0f), // 21
			glm::vec3(+0.8f, +0.9f, +0.5f), // Color
			glm::vec3(-1.0f, -1.0f, +1.0f), // 22
			glm::vec3(+0.5f, +0.8f, +0.5f), // Color
			glm::vec3(+1.0f, -1.0f, +1.0f), // 23
			glm::vec3(+0.9f, +1.0f, +0.2f), // Color
		};

		unsigned short stackIndices[] = {
			0,   1,  2,  0,  2,  3, // Top
			4,   5,  6,  4,  6,  7, // Front
			8,   9, 10,  8, 10, 11, // Right
			12, 13, 14, 12, 14, 15, // Left
			16, 17, 18, 16, 18, 19, // Back
			20, 22, 21, 20, 23, 22, // Bottom
		};

		m_numVertices = sizeof(stackVerts) / sizeof(glm::vec3);
		m_numIndices = sizeof(stackIndices) / sizeof(unsigned short);

		m_vertices = new glm::vec3[m_numVertices];
		m_indices = new unsigned short[m_numIndices];

		unsigned int currentVertexBufferSize = Ball::VertexBufferSize();
		unsigned int currentIndexBufferSize = Ball::IndexBufferSize();

		memcpy(m_vertices, stackVerts, currentVertexBufferSize);
		memcpy(m_indices, stackIndices, currentIndexBufferSize);

		CreateBuffer(currentVertexBufferSize);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));


		CreateIndexBuffer(currentIndexBufferSize);
		//CreateVertexArrayObject();
	}
public:
	void Draw(void) override
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
		//glBindVertexArray(m_vertexArrayID);

		glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_SHORT, 0);
	}
protected:
	unsigned int VertexBufferSize(void) override
	{
		return m_numVertices * sizeof(glm::vec3);
	}
	unsigned int IndexBufferSize(void) override
	{
		return m_numIndices * sizeof(unsigned short);
	}
};

#endif