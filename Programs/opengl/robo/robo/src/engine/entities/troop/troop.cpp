#include "troop.h"
#include "../../engine.h"
#include "../../bullet/gun.h"

Troop::Troop(float radius, glm::vec3 plainPosition,
	glm::vec3 color)
	: m_lives(30), m_yElevation(5.0f)
{
	m_worldCoordinates = plainPosition + glm::vec3(0.0f, m_yElevation, 0.0f);
	m_cube = new Cube(radius, color, false);
	m_cube->Init();
	m_gun = new Gun();
	TroopDataInit();
}

const bool Troop::Draw(glm::mat4& proj, glm::mat4& view,
	glm::vec3& eyePos, glm::vec3& lightPos, UniformLocations* locations,
	Time* timeData, Terrain* terrain, std::vector<Entity*>& robots)
{
	m_cube->Draw(proj, view, m_translateMatrix, eyePos, lightPos, locations, timeData);
	if (WantsToShoot())
		Shoot(robots);

	return true;
}
const bool Troop::BulletAiring(void)
{
	return m_gun->BulletAiring();
}
const bool Troop::DetectBulletCollision(const glm::vec3& worldCoords,
	const float& circleRad)
{
	return glm::distance(m_worldCoordinates, worldCoords) < circleRad + m_circleRadius;
}
const bool Troop::Alive(void)
{
	return m_lives > 0;
}
void Troop::DeleteBuffers(void)
{
	m_cube->DeleteBuffers();
}
void Troop::RemoveLife(void)
{
	--m_lives;
}
glm::vec2 Troop::PlainPosition(void)
{
	return glm::vec2();
}
void Troop::Power(const power_t&& power, const std::vector<Entity*>& robots)
{
	if (power == Entity::power_t::SHOOT)
		if (WantsToShoot()) 
			Shoot(robots);
}
void Troop::DrawBullets(glm::mat4& proj, glm::mat4& view, glm::vec3& eyePos,
	glm::vec3& lightPos, UniformLocations* locations, Time* time,
	Terrain* terrain, std::vector<Entity*>& vec)
{
	m_gun->Draw(proj, view, eyePos, lightPos, locations, time, terrain, vec);
}
void Troop::SendUniformData(glm::mat4& proj, glm::mat4& view, glm::mat4& model,
	glm::vec3& eyePos, glm::vec3& lightPos, UniformLocations* locations, Time* time)
{
	glUniformMatrix4fv(locations->m_uniLocProjection, 1, GL_FALSE, &proj[0][0]);
	glUniformMatrix4fv(locations->m_uniLocView, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(locations->m_uniLocModel, 1, GL_FALSE, &model[0][0]);
	glUniform3fv(locations->m_uniLocLightPosition, 1, &lightPos[0]);
	glUniform3fv(locations->m_uniLocEyePosition, 1, &eyePos[0]);
	glUniform1f(locations->m_uniLocTime, (float)(time->currentTime - time->beginning).count() / 1000000000);
}
void Troop::TroopDataInit(void)
{
	m_translateMatrix = glm::translate(m_worldCoordinates);
}
const bool Troop::WantsToShoot(void)
{
	int random = rand() % 25;
	return random == 13;
}
void Troop::Shoot(const std::vector<Entity*>& robots)
{
	for (auto& i : robots)
	{
		if (WantsToShoot())
		{
			glm::vec3 direction = glm::normalize(i->Position() - m_worldCoordinates);
			m_gun->Shoot(direction, m_worldCoordinates);
		}
	}
}