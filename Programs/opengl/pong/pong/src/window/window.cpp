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
	m_game->Init();
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
}
const bool Window::WindowIsOpen(void)
{
	return !glfwWindowShouldClose(m_glfwWindow);
}