#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>

#include "window.h"
#include "../log.h"
#include "../camera/camera.h"
#include "../terrain/terrain.h"

Window::Window(unsigned int width, unsigned int height, const char* title)
	: m_width(width), m_height(height), m_title(title)
{
	GLFWInit();
	WindowInit();
	GLEWInit();
	AfterGLEWInit();
}
Window::~Window(void)
{

}
void Window::Draw(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.2f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 transformMatrix = glm::perspective(glm::radians(60.0f), (float)m_width / m_height, 0.1f, 500.0f) *
		m_camera->GetWorldToViewMatrix();
	m_terrain->Draw(transformMatrix);
}
void Window::Update(void)
{
	glfwSwapBuffers(m_glfwWindow);
	glfwPollEvents();

	PollKeys();
}
const bool Window::WindowOpen(void)
{
	return !glfwWindowShouldClose(m_glfwWindow)
		&& !(glfwGetKey(m_glfwWindow, GLFW_KEY_ESCAPE));
}
void Window::PollKeys(void)
{
	PollMouseMovement();
	PollCameraMovement();
}
void Window::PollCameraMovement(void)
{
	if (!glfwGetKey(m_glfwWindow, GLFW_KEY_R))
	{
		m_camera->SetSpeedBackToDefault();
	}
	else
	{
		m_camera->SpeedUp();
	}
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_W))
	{
		m_camera->MoveForward();
	}
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_S))
	{
		m_camera->MoveBackward();
	}
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_A))
	{
		m_camera->MoveLeft();
	}
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_D))
	{
		m_camera->MoveRight();
	}
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_SPACE))
	{
		m_camera->MoveUp();
	}
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_LEFT_SHIFT))
	{
		m_camera->MoveDown();
	}
}
void Window::PollMouseMovement(void)
{
	double x, y;
	glfwGetCursorPos(m_glfwWindow, &x, &y);
	m_camera->MouseUpdate(glm::vec2(x, y));
}
void Window::WindowInit(void)
{
	m_glfwWindow = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
	glfwMakeContextCurrent(m_glfwWindow);
	if (!m_glfwWindow)
	{
		Error("failed to initialize window");
		glfwTerminate();
		std::cin.get();
		exit(1);
	}
	glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void Window::GLFWInit(void)
{
	if (!glfwInit())
	{
		Error("failed to initialize GLFW");
		glfwTerminate();
		std::cin.get();
		exit(1);
	}
}
void Window::GLEWInit(void)
{
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		Error("failed to initialize GLEW");
		glfwTerminate();
		std::cin.get();
		exit(1);
	}
}
void Window::AfterGLEWInit(void)
{
	glEnable(GL_DEPTH_TEST);

	m_terrain = new Terrain(100.0f, 100.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	m_camera = new Camera;
}