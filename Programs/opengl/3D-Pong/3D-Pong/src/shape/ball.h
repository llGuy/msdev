#ifndef BALL_HEADER
#define BALL_HEADER

#include "shape.h"

#include <iostream>

class Ball
	: public Shape
{
public:
	explicit Ball(glm::vec3 ballDirection)
		: m_ballDirection(ballDirection)
	{
		glm::vec3 verts[]
		{
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),

			glm::vec3(1.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),

			glm::vec3(-1.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 1.0f)
		};

		unsigned short indices[]
		{
			0, 1, 2
		};

		m_numVertices = sizeof(verts) / (3 * sizeof(float));
		m_numIndices = sizeof(indices) / sizeof(unsigned short);

		m_vertices = new glm::vec3[m_numVertices];
		m_indices = new unsigned short[m_numIndices];

		memcpy(m_vertices, verts, m_numVertices * (3 * sizeof(float)));
		memcpy(m_indices, indices, m_numIndices * sizeof(unsigned short));

		CreateBuffer();
		CreateIndexBuffer();
		CreateVertexBufferObject();
	}
public:
	void Draw(glm::mat4) override
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
		glBindVertexArray(m_vertexArrayObjectID);

		glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_SHORT, 0);
	}
private:
	glm::vec3 m_ballDirection;
	glm::vec3 m_translateVector;
	glm::vec3 m_ballSpeed;
};

#endif