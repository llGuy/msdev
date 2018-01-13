#ifndef PLAYER_HEADER
#define PLAYER_HEAEDER

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GLFW/glfw3.h>

class Player
{
public:
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

	explicit Player(glm::vec3 position, glm::vec3 viewDirection, GLFWwindow* window, float speed)
	{
		m_position = position;
		m_position.y += 0.7f;
		m_viewDirection = viewDirection;
		m_up = glm::vec3(0.0f, 1.0f, 0.0f);
		m_speed = speed;

		double x, y;
		glfwGetCursorPos(window, &x, &y);

		m_oldMousePosition.x = (float)x;
		m_oldMousePosition.y = (float)y;
	}
	glm::vec3& Position(void)
	{
		return m_position;
	}
	glm::mat4 ViewMatrix(void)
	{
		//m_viewDirection = glm::vec3();
		return glm::lookAt(m_position, m_position + m_viewDirection, m_up);
	}

	void Move(move_t move, float y)
	{
		if (move == FORWARD)
		{
			glm::vec3 toMoveVector = glm::vec3(m_viewDirection.x, 0.0f, m_viewDirection.z);
			m_position += toMoveVector * m_speed;
		}
		else if (move == BACKWARD)
		{
			glm::vec3 toMoveVector = glm::vec3(m_viewDirection.x, 0.0f, m_viewDirection.z);
			m_position -= toMoveVector * m_speed;
		}
		m_position.y = y + 0.7f;
	}
	void Strafe(strafe_t strafe, float y)
	{
		if (strafe == RIGHT)
		{
			glm::vec3 strafeDirection = glm::cross(m_viewDirection, m_up);
			m_position += strafeDirection * m_speed;
		}
		else if (strafe == LEFT)
		{
			glm::vec3 strafeDirection = glm::cross(m_viewDirection, m_up);
			m_position -= strafeDirection * m_speed;
		}
		m_position.y = y + 0.7f;
	}
	void Look(glm::vec2 newMousePosition)
	{
		glm::vec2 mouseDelta = newMousePosition - m_oldMousePosition;
		m_viewDirection = glm::mat3(glm::rotate(glm::radians(-mouseDelta.x) * 0.02f, m_up)) * m_viewDirection;
		glm::vec3 toRotateAround = glm::cross(m_viewDirection, m_up);
		m_viewDirection = glm::mat3(glm::rotate(glm::radians(-mouseDelta.y) * 0.02f, toRotateAround)) * m_viewDirection;
		m_oldMousePosition = newMousePosition;
	}
private:
	glm::vec3 m_position;
	glm::vec3 m_viewDirection;
	glm::vec3 m_up;
	float m_speed;
	glm::vec2 m_oldMousePosition;
};

#endif