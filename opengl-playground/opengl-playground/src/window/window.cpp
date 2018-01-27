#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>

#include "../player/player.h"

#include "window.h"
#include "../log.h"
#include "../blocks/handler.h"
#include "../camera/camera.h"
#include "../terrain/terrain.h"
#include "../water/water.h"

static void KeyCallback(GLFWwindow* window, int key, int, int action, int)
{
	Window* p = (Window*)(glfwGetWindowUserPointer(window));
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_T)
		{
			if (p->CameraPlayerView())
				p->CameraPlayerView() = false;
			else p->CameraPlayerView() = true;
		}
	}
}
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
	glm::vec3 sky = m_terrain->Sky();
	glClearColor(sky.r, sky.g, sky.b, 0.2f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::vec3 eyePos;
	if (m_cameraPlayerView)
	{
		m_view = m_camera->GetWorldToViewMatrix();
		eyePos = m_camera->GetEyePosition();
	}
	else
	{
		m_view = m_player->ViewMatrix();
		eyePos = m_player->Position();
	}
	m_terrain->Draw(m_projMat, m_view, eyePos);
	m_bh->Draw(m_projMat, m_view, eyePos, m_terrain->LP());
	//m_water->Draw(m_projMat, viewMat);
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
	if (m_cameraPlayerView)
	{
		if (!glfwGetKey(m_glfwWindow, GLFW_KEY_R))
			m_camera->SetSpeedBackToDefault();
		else
			m_camera->SpeedUp();
		if (glfwGetKey(m_glfwWindow, GLFW_KEY_W))
			m_camera->MoveForward();
		if (glfwGetKey(m_glfwWindow, GLFW_KEY_S))
			m_camera->MoveBackward();
		if (glfwGetKey(m_glfwWindow, GLFW_KEY_A))
			m_camera->MoveLeft();
		if (glfwGetKey(m_glfwWindow, GLFW_KEY_D))
			m_camera->MoveRight();
		if (glfwGetKey(m_glfwWindow, GLFW_KEY_SPACE))
			m_camera->MoveUp();
		if (glfwGetKey(m_glfwWindow, GLFW_KEY_LEFT_SHIFT))
			m_camera->MoveDown();
	}
	else
	{
		if (glfwGetKey(m_glfwWindow, GLFW_KEY_W))
			m_player->Move(FPSPlayer::FORWARD, m_terrain->GetYPosOfPlayer(m_player->Position().x, m_player->Position().z, m_player->Position().y));
		if (glfwGetKey(m_glfwWindow, GLFW_KEY_S))
			m_player->Move(FPSPlayer::BACKWARD, m_terrain->GetYPosOfPlayer(m_player->Position().x, m_player->Position().z));
		if (glfwGetKey(m_glfwWindow, GLFW_KEY_A))
			m_player->Strafe(FPSPlayer::LEFT, m_terrain->GetYPosOfPlayer(m_player->Position().x, m_player->Position().z));
		if (glfwGetKey(m_glfwWindow, GLFW_KEY_D))
			m_player->Strafe(FPSPlayer::RIGHT, m_terrain->GetYPosOfPlayer(m_player->Position().x, m_player->Position().z));
	}

	if (glfwGetMouseButton(m_glfwWindow, GLFW_MOUSE_BUTTON_LEFT))
	{
		double x, y;
		glfwGetCursorPos(m_glfwWindow, &x, &y);
		std::cout << "pressing left button" << std::endl;
		/*glm::vec3 start = glm::unProject(glm::vec3(x, m_height - y, 0.0f), m_view, m_projMat, glm::vec4(0.0f, 0.0f, m_width, m_height));
		glm::vec3 end = glm::unProject(glm::vec3(x, m_height - y, 1.0f), m_view, m_projMat, glm::vec4(0.0f, 0.0f, m_width, m_height));
		glm::vec3 origin = m_camera->GetEyePosition();
		glm::vec3 direction = glm::normalize(end - start);*/
		
		/*float winz;
		glReadPixels(m_width / 2, m_height / 2, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winz);
		//std::cout << "IN:  " << x << " " << m_height - y << " " <<  1.0f - winz << std::endl;
		//std::cout << winz << std::endl;
		glm::vec3 objpt = glm::unProject(glm::vec3(x, m_height - y, winz), m_camera->GetWorldToViewMatrix(), m_projMat, glm::vec4(0.0f, 0.0f, m_width, m_height));
		std::cout <<"OUT: " << objpt.x << " " << objpt.y << " " << objpt.z << std::endl;*/
		
		GLfloat depthComp;
		glReadPixels(m_width / 2, m_height / 2, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depthComp);
		GLfloat clip_z = (depthComp - 0.5f) * 2.0f;
		std::cout << (depthComp - 0.5f) * 2.0f << std::endl;
		float far = 500.0f;
		float near = 0.1f;
		GLfloat world_z = ((far - near) / 2)*clip_z + (far + near) / 2;
		GLfloat z = ((far - near) / 2) * depthComp + (near + far) / 2;
		glm::vec3 objpt = glm::unProject(glm::vec3(0.0f, 0.0f, depthComp), 
			m_view, m_projMat, glm::vec4(0.0f, 0.0f, m_width, m_height));
	//	std::cout << objpt.x << " " << objpt.y << " " << objpt.z << std::endl;
	//	std::cout << m_camera->GetEyePosition().x << " " << m_camera->GetEyePosition().y << " " << m_camera->GetEyePosition().z << std::endl;
		//std::cout << worldZ << std::endl;

		std::cout << objpt.x << " " << objpt.y << " " << objpt.z << std::endl;
	}
}
void Window::PollMouseMovement(void)
{
	double x, y;
	glfwGetCursorPos(m_glfwWindow, &x, &y);
	if(m_cameraPlayerView) m_camera->MouseUpdate(glm::vec2(x, y));
	else m_player->Look(glm::vec2(x, y));
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
	glfwSetKeyCallback(m_glfwWindow, KeyCallback);
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
bool& Window::CameraPlayerView(void)
{
	return m_cameraPlayerView;
}
void Window::AfterGLEWInit(void)
{
	glEnable(GL_DEPTH_TEST);

	Terrain::TerrainDimensions dim = {200.0f, 200.0f, 20.0f };
	m_terrain = new Terrain(dim);
	m_camera = new Camera;
	FPSPlayer::FPSPlayerData pd = { glm::vec3(0.0f, m_terrain->GetYPosOfPlayer(0.0f, 0.0f), 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), 0.02f };
	m_player = new FPSPlayer(pd, m_glfwWindow);

	m_projMat = glm::perspective(glm::radians(60.0f), (float)m_width / m_height, 0.1f, 500.0f);

	m_cameraPlayerView = true;

	m_bh = new BlockHandler();
	m_water = new Water(glm::vec3(0.0f, 19.0f, 0.0f), 5.0f);
}