#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include <GLFW\glfw3.h>
#include <math.h>
#include "..\entities\snake.h"

class Camera
{
public:
	explicit Camera(void)
		: m_UP_VECTOR(0.0f, 1.0f, 0.0f), m_viewDirection(0.0f, 0.0f, -1.0f),
		m_cameraPosition(0.0f, 0.0f, 0.0f), m_isLookingAtCenterOfGrid(false), m_isLookingAtSnake(true),
		m_rotationAngle(60.0f, 60.0f), m_distanceToSnake(3.0f)
	{
	}
public:
	void Init(GLFWwindow* window)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		m_oldMousePosition.x = (float)x;
		m_oldMousePosition.y = (float)y;
	}
	bool& IsLookingAtCenterOfGrid(void)
	{
		return m_isLookingAtCenterOfGrid;
	}
	void LookAtCenterOfGrid(void)
	{
		m_viewDirection = glm::vec3(0.0f, 0.0f, -10.0f) - m_cameraPosition;
	}
	void MouseUpdate(const glm::vec2& newMousePosition)
	{
		glm::vec2 mouseDelta = newMousePosition - m_oldMousePosition;

		m_rotationAngle.x -= mouseDelta.x * 0.5f;
		m_rotationAngle.y -= mouseDelta.y * 0.5f;

		m_oldMousePosition = newMousePosition;
	}
	glm::mat4 GetWorldToViewMatrix(Snake* snake)
	{
		Shape::ShapeVertices* verts = snake->Head()->ShapeVerts();

		if (m_isLookingAtSnake)
		{
			m_viewDirection = glm::vec3(-sin(glm::radians(m_rotationAngle.x)), -cos(glm::radians(m_rotationAngle.y)),
				-cos(glm::radians(m_rotationAngle.x)));
			m_cameraPosition.x = (verts->m_right - 0.5f) - m_viewDirection.x * m_distanceToSnake;
			m_cameraPosition.y = (verts->m_top - 0.5f) - m_viewDirection.y * m_distanceToSnake;
			m_cameraPosition.z = (verts->m_front - 0.5f) - m_viewDirection.z * m_distanceToSnake;
		}
		
		return glm::lookAt(m_cameraPosition, m_cameraPosition + m_viewDirection, m_UP_VECTOR);
	}
	glm::vec2 MousePosition(void)
	{
		return m_oldMousePosition;
	}
	void MoveForward(void)
	{
		m_cameraPosition += m_viewDirection * 0.02f;
	}
	void MoveBackward(void)
	{
		m_cameraPosition -= m_viewDirection * 0.02f;
	}
private:
	glm::vec3 m_cameraPosition;
	glm::vec3 m_viewDirection;
	glm::vec2 m_oldMousePosition;
	
	glm::vec2 m_rotationAngle;
	float m_distanceToSnake;

	const glm::vec3 m_UP_VECTOR;
	bool m_isLookingAtCenterOfGrid;
	bool m_isLookingAtSnake;
};

#endif