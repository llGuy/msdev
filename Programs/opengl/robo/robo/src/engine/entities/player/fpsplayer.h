#ifndef PLAYER_HEADER
#define PLAYER_HEAEDER

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class FPSPlayer
{
public:
	struct FPSPlayerData
	{
		glm::vec3 position;
		glm::vec3 viewDirection;
		float speed;
		float height;
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

	explicit FPSPlayer(FPSPlayerData pData)
		:	m_pData(pData),
			m_up(0.0f, 1.0f, 0.0f)
	{
		m_pData.position.y += m_pData.height;
		m_viewBobbing = +0.002f;
		m_viewBobbingDelta = m_viewBobbing;
		m_jumpingSpeed = 0.5f;
		m_jumpingSpeedDelta = 2.0f;
	}
	glm::vec3& Position(void)
	{
		return m_pData.position;
	}
	glm::mat4 ViewMatrix(void)
	{
		if (m_jumping)
		{

		}
		return glm::lookAt(m_pData.position, m_pData.position + m_pData.viewDirection, m_up);
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
		m_pData.position.y = y + 0.7f;
	}
	void ViewBobbing(void)
	{
		if (m_running) m_viewBobbing += m_viewBobbingDelta * 1.5f;
		else m_viewBobbing += m_viewBobbingDelta;
		if (m_pData.position.y + m_viewBobbing > m_pData.position.y + 0.1f || 
			m_pData.position.y + m_viewBobbing < m_pData.position.y)
			m_viewBobbingDelta *= -1.0f;

		m_pData.position.y += m_viewBobbing;
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
		m_pData.position.y = y + 0.7f;
	}
	void InitializeJumping(void)
	{
		m_jumpingHeightStart = m_pData.position.y;
		m_jumpingHeightMax = m_pData.position.y + 1.0f;
		m_jumpingSpeedDelta = 2.0f;
		m_isJumpingUp = true;
	}
	void Jump(void)
	{
		if (m_pData.position.y > m_jumpingHeightMax)
		{
			m_jumpingSpeedDelta = 1 / m_jumpingSpeedDelta;
			m_isJumpingUp = false;
		}
		if (m_isJumpingUp) m_pData.position.y += m_jumpingSpeed;
		else m_pData.position.y -= m_jumpingSpeed;
		
		m_jumpingSpeed /= m_jumpingSpeedDelta;
	}
	void Look(glm::vec2 newMousePosition)
	{
		glm::vec2 mouseDelta = newMousePosition - m_oldMousePosition;
		m_pData.viewDirection = glm::mat3(glm::rotate(glm::radians(-mouseDelta.x) * 0.02f, m_up)) * m_pData.viewDirection;
		glm::vec3 toRotateAround = glm::cross(m_pData.viewDirection, m_up);
		m_pData.viewDirection = glm::mat3(glm::rotate(glm::radians(-mouseDelta.y) * 0.02f, toRotateAround)) * m_pData.viewDirection;
		m_oldMousePosition = newMousePosition;
	}
	bool& Running(void)
	{
		return m_running;
	}
	bool& Jumping(void)
	{
		return m_jumping;
	}
	void SpeedUp(void)
	{
		m_pData.speed *= 2;
	}
	void NormalSpeed(float speed)
	{
		m_pData.speed = speed;
	}
private:
	FPSPlayerData m_pData;
	glm::vec3 m_up;
	glm::vec2 m_oldMousePosition;
	float m_viewBobbing;
	float m_viewBobbingDelta;
	bool m_running;
	bool m_jumping;
	float m_jumpingSpeed;
	float m_jumpingSpeedDelta;
	float m_jumpingHeightMax;
	float m_jumpingHeightStart;
	bool m_isJumpingUp;
};

#endif