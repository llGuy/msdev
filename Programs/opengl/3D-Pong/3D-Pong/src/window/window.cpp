#include "window.h"

#include <GLFW\glfw3.h>

Window::Window(unsigned int width, unsigned int height, const char* title)
	: m_width(width), m_height(height), m_title(title), m_game()
{
}
Window::~Window(void)
{
}
void Window::Update(void)
{
	glfwSwapBuffers(m_glfwWindow);
	glfwPollEvents();
}
void Window::Draw(void)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_game.Draw();
}
void Window::Init(void)
{
	m_glfwWindow = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
	glfwMakeContextCurrent(m_glfwWindow);
}
void Window::AfterGLEWInit(void)
{
	m_game.Init();
}
const bool Window::FailedToCreateWindow(void)
{
	return m_glfwWindow;
}
const bool Window::WindowIsClosed(void)
{
	return glfwWindowShouldClose(m_glfwWindow);
}
void Window::DestroyWindow(void)
{
	glfwDestroyWindow(m_glfwWindow);
}
const unsigned int Window::Width(void)
{
	return m_width;
}
const unsigned int Window::Height(void)
{
	return m_height;
}
const char* Window::Title(void)
{
	return m_title;
}