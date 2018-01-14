#include "robot.h"

#include <GL/glew.h>

#include "../primitives/vertex.h"
#include "../engine.h"

#include "../data/time.h"
#include "../bullet/gun.h"

Robot::Robot(float radius, glm::vec2 plainPosition, glm::vec3 color)
	: m_cubeRadius(radius)
{
	m_cube = new Cube(m_cubeRadius, color, true);
	m_translateVectorPlainPosition = plainPosition;
	m_gun = new Gun(0.1f);
	m_cube->Init();
	RobotDataInit();
}
const bool Robot::Draw(glm::mat4& proj, glm::mat4& view, 
	glm::vec3& eyePos, glm::vec3& lightPos, UniformLocations* locations, 
	Time* timeData, Terrain* terrain, FPSPlayer* player)
{
	m_hitPlayer = false;
	m_cube->Draw(proj, view, m_translateMatrix, eyePos, lightPos, locations, timeData);
	if (WantsToShoot()) Shoot(eyePos);
	if (m_gun->BulletAiring()) m_hitPlayer = m_gun->Draw(proj, view, eyePos, lightPos, locations, timeData, terrain, player);
	return m_hitPlayer;
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
void Robot::RobotDataInit(void)
{
	m_lives = static_cast<unsigned int>(m_cubeRadius * 4);
	m_robotSpeed = 0.007f / m_cubeRadius;
	m_viewDirection = glm::vec2(1.0f, 0.0f);
	m_circleRadius = glm::distance(glm::vec3(0.0f), glm::vec3(+m_cubeRadius, +m_cubeRadius, +m_cubeRadius));
}
void Robot::DeleteBuffers(void)
{
	m_cube->DeleteBuffers();
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
	m_viewDirection = glm::normalize(playerPosition - m_translateVectorPlainPosition);
	m_translateVectorPlainPosition += m_viewDirection * m_robotSpeed;
}
const bool Robot::DetectCollision(glm::vec3 bullet, float bulletRadius)
{
	return glm::distance(m_worldCoordinates, bullet) < bulletRadius + m_circleRadius;
}
const bool Robot::Alive(void)
{
	return m_lives > 0;
}
void Robot::RemoveLife(void)
{
	--m_lives;
}
const bool Robot::WantsToShoot(void)
{
	return rand() % 511 == 3;
}
void Robot::Shoot(glm::vec3 playerPosition)
{
	m_gun->Shoot(glm::normalize(playerPosition - m_worldCoordinates), m_worldCoordinates + glm::vec3(0.0f, 0.5f, 0.0f));
}