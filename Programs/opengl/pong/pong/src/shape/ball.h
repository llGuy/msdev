#ifndef BALL_HEADER
#define BALL_HEADER

#include "shape.h"
#include <glm\gtx\transform.hpp>

class Ball
	: public Shape
{
public:
	explicit Ball(Color color)
		: m_transformMatrix(1.0f)
	{
		glm::vec3 stackVerts[] = {
			glm::vec3(-m_radius, +m_radius, +m_radius), // 0
			color.m_colorPs, // Color
			glm::vec3(+m_radius, +m_radius, +m_radius), // 1
			color.m_colorPs, // Color
			glm::vec3(+m_radius, +m_radius, -m_radius), // 2
			color.m_colorPs, // Color
			glm::vec3(-m_radius, +m_radius, -m_radius), // 3
			color.m_colorPs, // Color
			
			glm::vec3(-m_radius, +m_radius, -m_radius), // 4
			color.m_colorPs, // Color
			glm::vec3(+m_radius, +m_radius, -m_radius), // 5
			color.m_colorPs, // Color
			glm::vec3(+m_radius, -m_radius, -m_radius), // 6
			color.m_colorPs, // Color
			glm::vec3(-m_radius, -m_radius, -m_radius), // 7
			color.m_colorPs, // Color
			
			glm::vec3(+m_radius, +m_radius, -m_radius), // 8
			color.m_colorFB, // Color
			glm::vec3(+m_radius, +m_radius, +m_radius), // 9
			color.m_colorFB, // Color
			glm::vec3(+m_radius, -m_radius, +m_radius), // 10
			color.m_colorFB, // Color
			glm::vec3(+m_radius, -m_radius, -m_radius), // 11
			color.m_colorFB, // Color
			
			glm::vec3(-m_radius, +m_radius, +m_radius), // 12
			color.m_colorFB, // Color
			glm::vec3(-m_radius, +m_radius, -m_radius), // 13
			color.m_colorFB, // Color
			glm::vec3(-m_radius, -m_radius, -m_radius), // 14
			color.m_colorFB, // Color
			glm::vec3(-m_radius, -m_radius, +m_radius), // 15
			color.m_colorFB, // Color
			
			glm::vec3(+m_radius, +m_radius, +m_radius), // 16
			color.m_colorSs, // Color
			glm::vec3(-m_radius, +m_radius, +m_radius), // 17
			color.m_colorSs, // Color
			glm::vec3(-m_radius, -m_radius, +m_radius), // 18
			color.m_colorSs, // Color
			glm::vec3(+m_radius, -m_radius, +m_radius), // 19
			color.m_colorSs, // Color
			
			glm::vec3(+m_radius, -m_radius, -m_radius), // 20
			color.m_colorSs, // Color
			glm::vec3(-m_radius, -m_radius, -m_radius), // 21
			color.m_colorSs, // Color
			glm::vec3(-m_radius, -m_radius, +m_radius), // 22
			color.m_colorSs, // Color
			glm::vec3(+m_radius, -m_radius, +m_radius), // 23
			color.m_colorSs, // Color
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
		CreateVertexArrayObject();
		CreateIndexBuffer(currentIndexBufferSize);
	}
public:
	void Draw(glm::mat4 worldToViewMatrix, unsigned int uniformLocation) override
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
		glBindVertexArray(m_vertexArrayID);

		m_transformMatrix = worldToViewMatrix * glm::translate(glm::vec3(2.0f, 2.0f, -7.0f));

		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &m_transformMatrix[0][0]);

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
private:
	glm::vec3 m_translateVector;

	const float m_radius = 0.2f;

	glm::mat4 m_transformMatrix;
};

#endif