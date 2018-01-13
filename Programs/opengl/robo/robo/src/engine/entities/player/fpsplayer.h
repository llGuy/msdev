#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include <math.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtx/transform.hpp>

#include "../../bullet/gun.h"
#include "../../robot/robot.h"

class FPSPlayer
{
public:
	struct FPSPlayerData
	{
		glm::vec3 position;
		glm::vec3 viewDirection;
		float speed;
		float height;
		float viewBobbingValue;
		float runningDelta;
	};
	struct JumpData
	{
		glm::vec3 velocity;
		glm::vec3 gravity;
		bool jumping;
	};
	struct FlourishData
	{
		glm::vec3 velocity;
		glm::vec3 gravity;
		bool flourishing;
		float yInclination;
		float angle;
		unsigned int colorIndex;

		glm::vec3 rainbowColors[7] = 
		{
			glm::vec3(148.0f / 255.0f, 0.0f, 211.0f / 255.0f) * 0.6f,
			glm::vec3(75.0f / 255.0f, 0.0f, 130 / 255.0f) * 0.6f,
			glm::vec3(0.0f, 0.0f, 1.0f) * 0.6f,
			glm::vec3(0.0f, 1.0f, 0.0f) * 0.6f,
			glm::vec3(1.0f, 1.0f, 0.0f) * 0.6f,
			glm::vec3(1.0f, 0.5f, 0.0f) * 0.6f,
			glm::vec3(1.0f, 0.0f, 0.0f) * 0.6f
		};
	};
	enum move_t
	{
		FORWARD,

		BACKWARD
	};
	enum strafe_t
	{
		RIGHT,

		LEFT
	};

public:
	explicit FPSPlayer(FPSPlayerData pData)
		:	m_pData(pData),
			m_up(0.0f, 1.0f, 0.0f),
			m_gun()
	{
		m_pData.position.y += m_pData.height;
		m_viewBobbing = pData.viewBobbingValue;
		m_viewBobbingDelta = m_viewBobbing;
		m_runningDelta = pData.runningDelta;
		m_jd.jumping = false;
		m_fd.flourishing = false;
	}
public:
	// getter methods
	glm::vec3& Position(void)
	{
		return m_pData.position;
	}
	glm::mat4 ViewMatrix(float terrainHeight, Time* time)
	{
		if (m_fd.flourishing)
		{
			Flourish(static_cast<float>(time->deltaT));
			CheckFlourishLanding(terrainHeight);
		}
		if (m_jd.jumping)
		{
			Jump(static_cast<float>(time->deltaT));
			CheckJumpLanding(terrainHeight);
		}
		return glm::lookAt(m_pData.position, m_pData.position + m_pData.viewDirection, m_up);
	}
public:
	void ViewBobbing(void)
	{
		if (!m_jd.jumping && !m_fd.flourishing)
		{
			if (m_running) m_viewBobbing += m_viewBobbingDelta * 1.5f;
			else m_viewBobbing += m_viewBobbingDelta;
			if (m_pData.position.y + m_viewBobbing > m_pData.position.y + 0.1f ||
				m_pData.position.y + m_viewBobbing < m_pData.position.y)
				m_viewBobbingDelta *= -1.0f;

			m_pData.position.y += m_viewBobbing;
		}
	}
	void Move(move_t move, float y)
	{
		if (move == FORWARD)
		{
			glm::vec3 toMoveVector = glm::vec3(m_pData.viewDirection.x, 0.0f, m_pData.viewDirection.z);
			m_pData.position += toMoveVector * m_pData.speed;
		}
		else if (move == BACKWARD)
		{
			glm::vec3 toMoveVector = glm::vec3(m_pData.viewDirection.x, 0.0f, m_pData.viewDirection.z);
			m_pData.position -= toMoveVector * m_pData.speed;
		}
		if(!m_jd.jumping && !m_fd.flourishing)
			m_pData.position.y = y + m_pData.height;
	}
	void Strafe(strafe_t strafe, float y)
	{
		if (strafe == RIGHT)
		{
			glm::vec3 strafeDirection = glm::cross(m_pData.viewDirection, m_up);
			m_pData.position += strafeDirection * m_pData.speed;
		}
		else if (strafe == LEFT)
		{
			glm::vec3 strafeDirection = glm::cross(m_pData.viewDirection, m_up);
			m_pData.position -= strafeDirection * m_pData.speed;
		}
		if(!m_jd.jumping && !m_fd.flourishing)
			m_pData.position.y = y + m_pData.height;
	}
	void Look(glm::vec2 newMousePosition)
	{
		glm::vec2 mouseDelta = newMousePosition - m_oldMousePosition;
		m_pData.viewDirection = glm::mat3(glm::rotate(glm::radians(-mouseDelta.x) * 0.02f, m_up)) * m_pData.viewDirection;
		glm::vec3 toRotateAround = glm::cross(m_pData.viewDirection, m_up);
		m_pData.viewDirection = glm::mat3(glm::rotate(glm::radians(-mouseDelta.y) * 0.02f, toRotateAround)) * m_pData.viewDirection;
		m_oldMousePosition = newMousePosition;
	}
public:
	void InitializeJump(double deltaT)
	{
		if (!m_jd.jumping)
		{
			m_jd.jumping = true;
			m_jd.gravity = glm::vec3(0.0f, -9.8f, 0.0f);
			m_jd.velocity = glm::vec3(0.0f, 3.5f, 0.0f);
		}
	}
	void InitializeFlourish(double deltaT)
	{
		if (!m_fd.flourishing)
		{
			m_fd.flourishing = true;
			m_fd.gravity = glm::vec3(0.0f, -9.8f, 0.0f);
			m_fd.velocity = glm::vec3(0.0f, 3.5f * 15.0f, 0.0f);
			m_fd.angle = 0.0f;
			m_fd.colorIndex = 0;
		}
	}
	void Jump(float deltaT)
	{
		m_pData.position = m_pData.position + m_jd.velocity * deltaT;
		m_jd.velocity = m_jd.velocity + m_jd.gravity * deltaT;
	}
	void Flourish(float deltaT)
	{
		m_pData.position = m_pData.position + m_fd.velocity * deltaT;
		m_fd.velocity = m_fd.velocity + m_fd.gravity * deltaT;

		m_fd.yInclination = static_cast<float>(-(rand() % 9));
		glm::vec3 directionOfBullet = glm::vec3(sin(glm::radians(m_fd.angle)), m_fd.yInclination, cos(glm::radians(m_fd.angle)));
		m_gun.Shoot(directionOfBullet, m_pData.position + glm::vec3(0.0f, 1.0f, 0.0f), m_fd.rainbowColors[m_fd.colorIndex % 7]);
		++m_fd.colorIndex;

		m_fd.yInclination = static_cast<float>(-(rand() % 9));
		directionOfBullet = glm::vec3(sin(glm::radians(180 + m_fd.angle)), m_fd.yInclination, cos(glm::radians(180 + m_fd.angle)));
		m_gun.Shoot(directionOfBullet, m_pData.position + glm::vec3(0.0f, 1.0f, 0.0f), m_fd.rainbowColors[m_fd.colorIndex % 7]);
		++m_fd.colorIndex;

		m_fd.angle += 1.0f;
	}
	void CheckJumpLanding(float terrainHeight)
	{
		if (m_pData.position.y - m_pData.height < terrainHeight)
		{
			m_jd.jumping = false;
			m_pData.position.y = terrainHeight + m_pData.height;
		}
	}
	void CheckFlourishLanding(float terrainHeight)
	{
		if (m_pData.position.y - m_pData.height < terrainHeight)
		{
			m_fd.flourishing = false;
			m_pData.position.y = terrainHeight + m_pData.height;
		}
	}
public:
	void DrawBullets(glm::mat4& proj, glm::mat4& view, glm::vec3& eyePos,
		glm::vec3& lightPos, UniformLocations* locations, Time* time, Terrain* terrain, std::vector<Robot>& vec)
	{
		m_gun.Draw(proj, view, eyePos, lightPos, locations, time, terrain, vec);
	}
	const bool BulletAiring(void)
	{
		return m_gun.BulletAiring();
	}
	void Shoot(void)
	{
		m_gun.Shoot(m_pData.viewDirection, m_pData.position);
	}
public:
	// other getters
	bool& Running(void)
	{
		return m_running;
	}
	void SpeedUp(void)
	{
		m_pData.speed *= m_runningDelta;
	}
	void NormalSpeed(float speed)
	{
		m_pData.speed = speed;
	}
public:
	// what happens when the player dies
	void Die(void)
	{
		std::cout << "dead" << std::endl;
	}
private:
	glm::vec3 m_up;
	glm::vec2 m_oldMousePosition;
	float m_viewBobbing;
	float m_viewBobbingDelta;
	float m_runningDelta;
	bool m_running;

	Gun m_gun;
	JumpData m_jd;
	FlourishData m_fd;
	FPSPlayerData m_pData;
};

#endif