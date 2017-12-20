#ifndef BALL_HEADER
#define BALL_HEADER

#include "shape.h"
#include "shape-data\shapegen.h"

#include <iostream>

class Ball
	: public Shape
{
public:
	explicit Ball(glm::vec3 ballDirection)
		: m_ballDirection(ballDirection)
	{
		m_ballData = Shapegen::MakeCube();
		CreateBuffer(m_ballData.vertexBufferSize(), m_ballData.m_vertices);
		CreateIndexBuffer(m_ballData.indexBufferSize(), m_ballData.m_indices);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 3 ,GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
	
		//CreateVertexBufferObject();
	}
public:
	void Draw(glm::mat4) override
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
		//glBindVertexArray(m_vertexArrayObjectID);

		glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_SHORT, 0);
	}
private:
	glm::vec3 m_ballDirection;
	glm::vec3 m_translateVector;
	glm::vec3 m_ballSpeed;
	
	ShapeData m_ballData;
};

#endif