#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>

#include "window.h"
#include "../log.h"

Window::Window(unsigned int width, unsigned int height, const char* title)
	: m_width(width), m_height(height), m_title(title), m_engine(0)
{
	minecraft::ent::Player::Name n = QueryName();
	// all initializations
	GLFWInit();
	WindowInit();
	GLEWInit();
	AfterGLEWInit(n);
}
Window::~Window(void)
{
}
void Window::Draw(void)
{ 
	glClearColor(0.0f, 0.2f, 0.8f, 0.2f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Window::Update(void)
{
	glfwSwapBuffers(m_glfwWindow);
	glfwPollEvents();
}
const bool Window::WindowOpen(void)
{
	return !glfwWindowShouldClose(m_glfwWindow)
		&& !(glfwGetKey(m_glfwWindow, GLFW_KEY_ESCAPE));
}
minecraft::ent::Player::Name Window::QueryName(void)
{
	Log("enter player name:");
	minecraft::ent::Player::Name name = minecraft::ent::Player::Name();
	std::cin >> name.name;
	return name;
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
	glfwSetWindowUserPointer(m_glfwWindow, this);
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
void Window::AfterGLEWInit(minecraft::ent::Player::Name pname)
{
	glEnable(GL_DEPTH_TEST);

	double x, y;
	glfwGetCursorPos(m_glfwWindow, &x, &y);
	m_engine.AfterGLEWInit(m_width, m_height, glm::vec2(x, y), pname);
}
void Window::PollKeys(void) 
{
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_W))
		m_engine.RecieveKeyInput(minecraft::Engine::key_t::W);
	/* other keys ... */
}
void Window::PollMouseMovement(void)
{

}