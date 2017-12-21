#include "window.h"
#include "..\game\game.h"
#include "..\init.h"

#include <GLFW\glfw3.h>

Window::Window(unsigned int width,
	unsigned int height,
	const char* title)
	: m_width(width),
	m_height(height),
	m_title(title), m_game(new Game())
{
	GLFWInit();
	Init();
	GLEWInit();
	InitAfterGLEWInit();
}
Window::~Window(void)
{
}
void Window::Init(void)
{
	m_glfwWindow = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
	glfwMakeContextCurrent(m_glfwWindow);
}
void Window::InitAfterGLEWInit(void)
{
	m_game->Init(m_width, m_height);
	glEnable(GL_DEPTH_TEST);
}
void Window::Draw(void)
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_game->Draw();
}
void Window::Update(void)
{
	glfwSwapBuffers(m_glfwWindow);
	glfwPollEvents();

	PollKeys();
}
const bool Window::WindowIsOpen(void)
{
	return !glfwWindowShouldClose(m_glfwWindow);
}
void Window::PollKeys(void)
{
	PollPaddleLeftMovement();
	PollPaddleRightMovement();
}
void Window::PollPaddleLeftMovement(void)
{
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_W))
	{
		m_game->PaddleLeft()->Action(Shape::MOVE_UP);
	}
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_S))
	{
		m_game->PaddleLeft()->Action(Shape::MOVE_DOWN);
	}
}
void Window::PollPaddleRightMovement(void)
{
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_UP))
	{
		m_game->PaddleRight()->Action(Shape::MOVE_UP);
	}
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_DOWN))
	{
		m_game->PaddleRight()->Action(Shape::MOVE_DOWN);
	}
}