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
			glm::vec3(1.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),

			glm::vec3(-1.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),

			glm::vec3(-1.0f, -1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f)
		};

		unsigned short indices[]
		{
			0, 1, 2
		};

		m_numVertices = sizeof(verts) / sizeof(glm::vec3);
		m_numIndices = sizeof(indices) / sizeof(unsigned short);

		m_vertices = new glm::vec3[m_numVertices];
		//m_indices = new unsigned short[m_numIndices];

		memcpy(m_vertices, verts, sizeof(verts));
		//memcpy(m_indices, indices, sizeof(indices));
		//for (unsigned int i = 0; i < m_numIndices; ++i)
			//m_indices[i] = indices[i];

		/*CreateBuffer(&m_bufferID, m_numVertices * sizeof(glm::vec3), m_vertices);
		CreateVertexArrayObject(&m_vertexArrayObjectID, &m_bufferID);
		CreateIndexBuffer(&m_indexBufferID, m_numIndices * sizeof(unsigned short), m_indices);
		*/

		glGenBuffers(1, &m_bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	
		glGenVertexArrays(1, &m_vertexArrayObjectID);
		glBindVertexArray(m_vertexArrayObjectID);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));

		glGenBuffers(1, &m_indexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}
public:
	void Draw(glm::mat4 viewProjectionMatrix) override
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
		
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char*)(sizeof(float) * 3));

		glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_SHORT, 0);
	}
private:
	glm::vec3 m_ballDirection;
	glm::vec3 m_translateVector;
	glm::vec3 m_ballSpeed;

	unsigned short m_indices[3] = {0,1,2};
};

#endif