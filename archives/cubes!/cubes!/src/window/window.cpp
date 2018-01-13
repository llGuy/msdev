#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window.h"
#include "../log.h"
#include "../entities/cube.h"
#include "../camera/camera.h"

Window::Window(unsigned int width,
	unsigned int height,
	const char* title)
	: m_width(width), m_height(height),
	m_title(title)
{
	GLFWInit();
	Init();
	GLEWInit();
	AfterGLEWInit();
}
Window::~Window(void)
{
	//deletions
}

//public:

void Window::Draw(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 cameraProjectionMatrix = m_perspectiveMatrix * m_camera->GetWorldToViewMatrix();
	m_cubes->Draw(cameraProjectionMatrix);
}

void Window::Update(void)
{
	glfwSwapBuffers(m_glfwWindow);
	glfwPollEvents();
	PollEvent();
}

const bool Window::WindowOpen(void)
{
	return !glfwWindowShouldClose(m_glfwWindow)
		&& !(glfwGetKey(m_glfwWindow, GLFW_KEY_ESCAPE));
}

void Window::Init(void)
{
	Log("initializing window");
	m_glfwWindow = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
	glfwMakeContextCurrent(m_glfwWindow);
	if (!m_glfwWindow)
	{
		Log("failed to initialize window");
		std::cin.get();
		exit(1);
	}
	glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowUserPointer(m_glfwWindow, this);
}
void Window::GLFWInit(void)
{
	Log("initializing GLFW");
	if (!glfwInit())
	{
		glfwTerminate();
		Log("failed to initialize GLFW");
		std::cin.get();
		exit(1);
	}
}
void Window::GLEWInit(void)
{
	Log("initializing GLEW");
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		glfwTerminate();
		Log("failed to initilize GLEW");
		std::cin.get();
		exit(1);
	}
}
void Window::AfterGLEWInit(void)
{
	glEnable(GL_DEPTH_TEST);

	m_cubes = new Cubes(50);
	m_camera = new Camera;
	m_perspectiveMatrix = glm::perspective(glm::radians(60.0f), (float)m_width / m_height, 0.1f, 30.0f);
}
void Window::PollEvent(void)
{
	PollCameraMovement();
	PollMouseMovement();
}
void Window::PollCameraMovement(void)
{
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_W))
	{
		m_camera->MoveForward();
	}
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_A))
	{
		m_camera->MoveLeft();
	}
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_S))
	{
		m_camera->MoveBackward();
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
	glm::vec2 newMousePos = glm::vec2(x, y);
	m_camera->MouseUpdate(newMousePos);
}