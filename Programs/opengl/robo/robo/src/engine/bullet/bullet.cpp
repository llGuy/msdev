#include <GL/glew.h>
#include <math.h>

#include "bullet.h"
#include "../engine.h"

Bullet::Bullet(glm::vec3 playerViewDirection,
	glm::vec3 playerEyePos)
	: m_cubeRadius(0.1f), m_buffer(), m_bulletSpeed(0.3f)
{
	Init(playerViewDirection, playerEyePos);
	CreateVertices();
	CreateIndices();
	CreateBuffer();
}
Bullet::~Bullet(void)
{
}
void Bullet::DeleteBuffer(void)
{
	m_buffer.DeleteBuffer();
}
void Bullet::Draw(glm::mat4& proj, glm::mat4& view, glm::vec3& eyePos,
	glm::vec3& lightPos, UniformLocations* locations, Time* time)
{
	m_buffer.BindAll();
	SendUnifromData(proj, view, m_translateMatrix, eyePos, lightPos, locations, time);
	glDrawElements(GL_TRIANGLES, m_indexData.numIndices, GL_UNSIGNED_SHORT, 0);
}
glm::vec2 Bullet::PlainPosition(void)
{
	return m_translateVectorPlainPosition;
}
void Bullet::Move(void)
{
	m_worldCoordinates += m_direction * m_bulletSpeed;
}
void Bullet::UpdateTranslateMatrix(void)
{
	m_translateMatrix = glm::translate(m_worldCoordinates);
	m_translateVectorPlainPosition = glm::vec2(m_worldCoordinates.x, m_worldCoordinates.z);
}
const bool Bullet::CollisionCheck(float heightOfTerrain, std::vector<Robot>& vec)
{
	for (unsigned short i = 0; i < vec.size(); ++i)
		if (vec[i].DetectCollision(m_worldCoordinates, m_circleRadius))
		{
			vec[i].RemoveLife();
			if (!vec[i].Alive()) vec.erase(vec.begin() + i);
			std::cout << vec.size() << " robots remain!" << std::endl;
			return true;
		}
	if (fabs(heightOfTerrain - m_worldCoordinates.y) < 0.7f)
		return true;
	return false;
}
void Bullet::Init(glm::vec3& playerViewDirection,
	glm::vec3 playerEyePos)
{
	m_direction = playerViewDirection;
	m_worldCoordinates = playerEyePos;
	m_translateVectorPlainPosition = glm::vec2(m_worldCoordinates.x,
		m_worldCoordinates.z);
}
void Bullet::CreateVertices(void)
{
	glm::vec3 color = glm::vec3(0.7f, 0.7f, 0.7f);
	Vertex stackVerts[] = {
		{ glm::vec3(-m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 0
		color }, // Color
	{ glm::vec3(+m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 1
	color }, // Color
	{ glm::vec3(+m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 2
	color }, // Color
	{ glm::vec3(-m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 3
	color }, // Color

	{ glm::vec3(-m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 4
	color }, // Color
	{ glm::vec3(+m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 5
	color }, // Color
	{ glm::vec3(+m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 6
	color }, // Color
	{ glm::vec3(-m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 7
	color }, // Color

	{ glm::vec3(+m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 8
	color }, // Color
	{ glm::vec3(+m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 9
	color }, // Color
	{ glm::vec3(+m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 10
	color }, // Color
	{ glm::vec3(+m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 11
	color }, // Color

	{ glm::vec3(-m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 12
	color }, // Color
	{ glm::vec3(-m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 13
	color }, // Color
	{ glm::vec3(-m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 14
	color }, // Color
	{ glm::vec3(-m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 15
	color }, // Color

	{ glm::vec3(+m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 16
	color }, // Color
	{ glm::vec3(-m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 17
	color }, // Color
	{ glm::vec3(-m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 18
	color }, // Color
	{ glm::vec3(+m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 19
	color }, // Color

	{ glm::vec3(+m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 20
	color }, // Color
	{ glm::vec3(-m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 21
	color }, // Color
	{ glm::vec3(-m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 22
	color }, // Color
	{ glm::vec3(+m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 23
	color }, // Color
	};
	m_vertexData.numVertices = sizeof(stackVerts) / sizeof(Vertex);
	m_vertexData.vData = new Vertex[m_vertexData.numVertices];
	memcpy(m_vertexData.vData, stackVerts, sizeof(Vertex) * m_vertexData.numVertices);
	m_circleRadius = glm::distance(glm::vec3(0.0f), glm::vec3(+m_cubeRadius, +m_cubeRadius, +m_cubeRadius));
}
void Bullet::CreateIndices(void)
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
const bool Bullet::EscapedTerrainLimits(float x, float z)
{
	return (fabs(m_worldCoordinates.x) > x / 2) || (fabs(m_worldCoordinates.z) > z / 2);
}
void Bullet::CreateBuffer(void)
{
	m_buffer.Init(m_vertexData, m_indexData);
}
void Bullet::SendUnifromData(glm::mat4 proj, glm::mat4 view, glm::mat4 model,
	glm::vec3 eyePos, glm::vec3 lightPos, UniformLocations* locations, Time* time)
{
	glUniformMatrix4fv(locations->m_uniLocProjection, 1, GL_FALSE, &proj[0][0]);
	glUniformMatrix4fv(locations->m_uniLocView, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(locations->m_uniLocModel, 1, GL_FALSE, &model[0][0]);
	glUniform3fv(locations->m_uniLocLightPosition, 1, &lightPos[0]);
	glUniform3fv(locations->m_uniLocEyePosition, 1, &eyePos[0]);
	glUniform1f(locations->m_uniLocTime, (float)(time->currentTime - time->beginning).count() / 1000000000);
}
const float& Bullet::CircleRadius(void)
{
	return m_circleRadius;
}
glm::vec3 Bullet::WorldCoords(void)
{
	return m_worldCoordinates;
}