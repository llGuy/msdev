#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include <GLFW\glfw3.h>
#include "..\entities\snake.h"

class Camera
{
public:
	explicit Camera(void)
		: m_UP_VECTOR(0.0f, 1.0f, 0.0f), m_viewDirection(0.0f, 0.0f, -1.0f), m_cameraPosition(0.0f, 0.0f, 0.0f), m_isLookingAtCenterOfGrid(true)
	{
	}
public:
	void Init(GLFWwindow* window)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		m_oldMousePosition.x = x;
		m_oldMousePosition.y = y;
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
		m_viewDirection = glm::mat3(glm::rotate(-glm::radians(mouseDelta.x) * 0.02f, m_UP_VECTOR)) * m_viewDirection;

		glm::vec3 toRotateAround = glm::cross(m_viewDirection, m_UP_VECTOR);
		m_viewDirection = glm::mat3(glm::rotate(-glm::radians(mouseDelta.y) * 0.02f, toRotateAround)) * m_viewDirection;

		m_oldMousePosition = newMousePosition;
	}
	glm::mat4 GetWorldToViewMatrix(Snake* snake) 
	{
		//return glm::mat4(1.0f);
		//return glm::lookAt(m_cameraPosition, m_cameraPosition + m_viewDirection, m_UP_VECTOR);

		Shape::ShapeVertices verts = snake->Head()->ShapeVerts();
		m_cameraPosition = glm::vec3(verts.m_right + 3.0f, verts.m_top + 3.0f,
			verts.m_front + 3.0f);
		if (m_isLookingAtCenterOfGrid)
			LookAtCenterOfGrid();
		
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

	const glm::vec3 m_UP_VECTOR;
	bool m_isLookingAtCenterOfGrid;
};

#endif