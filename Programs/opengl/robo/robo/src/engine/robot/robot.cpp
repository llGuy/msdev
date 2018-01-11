#include "robot.h"

#include <GL/glew.h>

#include "../primitives/vertex.h"
#include "../engine.h"

#include "../data/time.h"

Robot::Robot(float radius)
	: m_cubeRadius(radius), m_robotSpeed(0.001f), m_buffer()
{
	CreateVertices();
	CreateIndices();
	InitBuffer();
}
void Robot::Draw(glm::mat4& proj, glm::mat4& view, 
	glm::vec3& eyePos, glm::vec3& lightPos, UniformLocations* locations, Time* timeData)
{
	m_buffer.BindAll();
	SendUniformData(proj, view, m_translateMatrix, eyePos, lightPos, locations, timeData);
	glDrawElements(GL_TRIANGLES, m_indexData.numIndices, GL_UNSIGNED_SHORT, 0);
}
void Robot::SendUniformData(glm::mat4& proj, glm::mat4& view, glm::mat4& model, 
	glm::vec3& eyePos, glm::vec3& lightPos, UniformLocations* locations, Time* time)
{
	glUniformMatrix4fv(locations->m_uniLocProjection, 1, GL_FALSE, &proj[0][0]);
	glUniformMatrix4fv(locations->m_uniLocView, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(locations->m_uniLocModel, 1, GL_FALSE, &model[0][0]);
	glUniform3fv(locations->m_uniLocLightPosition, 1, &lightPos[0]);
	glUniform3fv(locations->m_uniLocEyePosition, 1, &eyePos[0]);
	glUniform1f(locations->m_uniLocTime, (float)(time->currentTime - time->beginning).count() / 1000000000);
}
void Robot::CreateVertices(void)
{
	glm::vec3 color = glm::vec3(0.2f, 0.2f, 0.2f);
	Vertex stackVerts[] = {
		{glm::vec3(-m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 0
		color}, // Color
		{glm::vec3(+m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 1
		color}, // Color
		{glm::vec3(+m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 2
		color}, // Color
		{glm::vec3(-m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 3
		color}, // Color

		{glm::vec3(-m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 4
		color}, // Color
		{glm::vec3(+m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 5
		color}, // Color
		{glm::vec3(+m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 6
		color}, // Color
		{glm::vec3(-m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 7
		color}, // Color

		{glm::vec3(+m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 8
		color}, // Color
		{glm::vec3(+m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 9
		color}, // Color
		{glm::vec3(+m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 10
		color}, // Color
		{glm::vec3(+m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 11
		color}, // Color

		{glm::vec3(-m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 12
		color}, // Color
		{glm::vec3(-m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 13
		color}, // Color
		{glm::vec3(-m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 14
		color}, // Color
		{glm::vec3(-m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 15
		color}, // Color

		{glm::vec3(+m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 16
		color}, // Color
		{glm::vec3(-m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 17
		color}, // Color
		{glm::vec3(-m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 18
		color}, // Color
		{glm::vec3(+m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 19
		color}, // Color

		{glm::vec3(+m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 20
		color}, // Color
		{glm::vec3(-m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 21
		color}, // Color
		{glm::vec3(-m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 22
		color}, // Color
		{glm::vec3(+m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 23
		color}, // Color
	};
	m_translateVectorPlainPosition = glm::vec2(0.0f, 0.0f);
	m_viewDirection = glm::vec2(1.0f, 0.0f);
	m_vertexData.numVertices = sizeof(stackVerts) / sizeof(Vertex);
	m_vertexData.vData = new Vertex[m_vertexData.numVertices];
	memcpy(m_vertexData.vData, stackVerts, sizeof(Vertex) * m_vertexData.numVertices);
	for (unsigned short i = 0; i < m_vertexData.numVertices; ++i)
		m_vertexData.vData[i].pos.y += m_cubeRadius;
}
void Robot::CreateIndices(void)
{
	unsigned short indices[]
	{
		0,   1,  2,  0,  2,  3, // Top
		4,   5,  6,  4,  6,  7, // Front
		8,   9, 10,  8, 10, 11, // Right
		12, 13, 14, 12, 14, 15, // Left
		16, 17, 18, 16, 18, 19, // Back
		20, 22, 21, 20, 23, 22, // Bottom
	};

	m_indexData.numIndices = sizeof(indices) / sizeof(unsigned short);
	m_indexData.iData = new unsigned short[m_indexData.numIndices];
	memcpy(m_indexData.iData, indices, sizeof(unsigned short) * m_indexData.numIndices);
}
void Robot::InitBuffer(void)
{
	m_buffer.Init(m_vertexData, m_indexData);
}
void Robot::UpdateTranslateMatrix(float height)
{
	m_worldCoordinates = glm::vec3(m_translateVectorPlainPosition.x, height, m_translateVectorPlainPosition.y);
	m_translateMatrix = glm::translate(m_worldCoordinates);
}
glm::vec2 Robot::PlainPosition(void)
{
	return glm::vec2(m_translateVectorPlainPosition.x, 
		m_translateVectorPlainPosition.y);
}
void Robot::MoveTowardsPlayer(glm::vec2 playerPosition)
{
	m_viewDirection = playerPosition - m_translateVectorPlainPosition;
	m_translateVectorPlainPosition += m_viewDirection * m_robotSpeed;
}