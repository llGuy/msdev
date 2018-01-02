#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class Camera
{
public:
	explicit Camera(void)
		: m_cameraPosition(0.0f, 0.0f, 0.0f),
		m_viewDirection(0.0f, 0.0f, -1.0f),
		m_up(0.0f, 1.0f, 0.0f), m_speed(0.02f)
	{
	}
public:
	glm::vec3 GetEyePosition(void)
	{
		return m_cameraPosition;
	}
	glm::mat4 GetWorldToViewMatrix(void) const
	{
		return glm::lookAt(m_cameraPosition, m_cameraPosition + m_viewDirection, m_up);
	}
	void MouseUpdate(const glm::vec2& newMousePosition)
	{
		glm::vec2 mouseDelta = newMousePosition - m_oldMousePosition;
		m_viewDirection = glm::mat3(glm::rotate(glm::radians(-mouseDelta.x) * 0.02f, m_up)) * m_viewDirection;
		glm::vec3 toRotateAround = glm::cross(m_viewDirection, m_up);
		m_viewDirection = glm::mat3(glm::rotate(glm::radians(-mouseDelta.y) * 0.02f, toRotateAround)) * m_viewDirection;
		m_oldMousePosition = newMousePosition;
	}
	void MoveForward(void)
	{
		glm::vec3 toMoveVector = glm::vec3(m_viewDirection.x, 0.0f, m_viewDirection.z);
		m_cameraPosition += toMoveVector * m_speed;
	}
	void MoveBackward(void)
	{
		glm::vec3 toMoveVector = glm::vec3(m_viewDirection.x, 0.0f, m_viewDirection.z);
		m_cameraPosition -= toMoveVector * m_speed;
	}
	void MoveRight(void)
	{
		glm::vec3 strafeDirection = glm::cross(m_viewDirection, m_up);
		m_cameraPosition += strafeDirection * m_speed;
	}
	void MoveLeft(void)
	{
		glm::vec3 strafeDirection = glm::cross(m_viewDirection, m_up);
		m_cameraPosition -= strafeDirection * m_speed;
	}
	void MoveUp(void)
	{
		m_cameraPosition += m_up * m_speed;
	}
	void MoveDown(void)
	{
		m_cameraPosition -= m_up * m_speed;
	}
	void SpeedUp(void)
	{
		m_speed = 0.2f;
	}
	void SetSpeedBackToDefault(void)
	{
		m_speed = 0.02f;
	}
private:
	glm::vec2 m_oldMousePosition;
	glm::vec3 m_cameraPosition;
	glm::vec3 m_viewDirection;
	glm::vec3 m_up;

	float m_speed;
};

#endif