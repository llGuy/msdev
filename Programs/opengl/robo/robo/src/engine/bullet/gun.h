#ifndef GUN_HEADER
#define GUN_HEADER

#include <vector>

#include "bullet.h"
#include "../terrain/terrain.h"
#include "../robot/robot.h"

class Gun
{
public:
	explicit Gun(void)
		: m_bullets()
	{
	}

	void Shoot(glm::vec3 playerViewDirection, glm::vec3 playerEyePos)
	{ 
		m_bullets.push_back(Bullet(playerViewDirection, playerEyePos));
	}
	void Draw(glm::mat4& proj, glm::mat4& view, glm::vec3& eyePos,
		glm::vec3& lightPos, UniformLocations* locations, Time* time, Terrain* terrain, std::vector<Robot>& vec)
	{
		MoveBullets(proj, view, eyePos, lightPos, locations, time, terrain, vec);
	}
	const bool BulletAiring(void)
	{
		return m_bullets.size() > 0;
	}
private:
	void MoveBullets(glm::mat4& proj, glm::mat4& view, glm::vec3& eyePos,
		glm::vec3& lightPos, UniformLocations* locations, Time* time, Terrain* terrain, std::vector<Robot>& vec)
	{
		for (unsigned short i = 0; i < m_bullets.size(); ++i)
		{
			if (m_bullets[i].CollisionCheck(terrain->GetYPosOfPlayer(m_bullets[i].PlainPosition().x, m_bullets[i].PlainPosition().x), vec) ||
				m_bullets[i].EscapedTerrainLimits(terrain->Dimensions().x, terrain->Dimensions().y))
			{
				m_bullets[i].DeleteBuffer();
				m_bullets.erase(m_bullets.begin() + i);
			}
			else
			{
				m_bullets[i].Move();
				m_bullets[i].UpdateTranslateMatrix();
				m_bullets[i].Draw(proj, view, eyePos, lightPos, locations, time);
			}
		}
	}
private:
	std::vector<Bullet> m_bullets;
};

#endif