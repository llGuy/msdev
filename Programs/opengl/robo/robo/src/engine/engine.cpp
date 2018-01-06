#include "engine.h"

#include <GL/glew.h>

RoboEngine::RoboEngine(float windowWidth, float windowHeight)
	: m_shaders(VSH, FSH, GSH),
	m_lighting({ glm::vec3(0.0f, 100.0f, 0.0f) })
{ 
	m_terrain = new Terrain({ TERRAIN_X, TERRAIN_Z, TERRAIN_MAX_HEIGHT }, Biome::PLANES);
	m_fps = new FPSPlayer({ glm::vec3(ORIGINAL_FPSPLAYER_POSITION.x,
		m_terrain->GetYPosOfPlayer(ORIGINAL_FPSPLAYER_POSITION.x, ORIGINAL_FPSPLAYER_POSITION.z), ORIGINAL_FPSPLAYER_POSITION.z),
		ORIGINAL_FPSPLAYER_VIEW_DIRECTION, m_playerSpeed, m_playerHeight });
	MatricesInit(windowWidth, windowHeight);
	CompileShaders();
	GetUniformLocations();
}
RoboEngine::~RoboEngine(void)
{
}
void RoboEngine::Draw(void)
{
	glm::vec3 m_skyColor = m_terrain->Sky();
	glClearColor(m_skyColor.r, m_skyColor.g, m_skyColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	m_shaders.UseProgram();
	UpdateMatrices();
	m_terrain->Draw(m_transformMatrices.projection, m_transformMatrices.view, m_fps->Position(), m_lighting.lightPosition, &m_uniformLocations);
}
void RoboEngine::KeyInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W))
		m_fps->Move(FPSPlayer::FORWARD, m_terrain->GetYPosOfPlayer(m_fps->Position().x, m_fps->Position().z));
	if (glfwGetKey(window, GLFW_KEY_S))
		m_fps->Move(FPSPlayer::BACKWARD, m_terrain->GetYPosOfPlayer(m_fps->Position().x, m_fps->Position().z));
	if (glfwGetKey(window, GLFW_KEY_A))
		m_fps->Strafe(FPSPlayer::LEFT, m_terrain->GetYPosOfPlayer(m_fps->Position().x, m_fps->Position().z));
	if (glfwGetKey(window, GLFW_KEY_D))
		m_fps->Strafe(FPSPlayer::RIGHT, m_terrain->GetYPosOfPlayer(m_fps->Position().x, m_fps->Position().z));
}
void RoboEngine::MouseInput(GLFWwindow* window)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	m_fps->Look(glm::vec2(x, y));
}
void RoboEngine::MatricesInit(float windowWidth, float windowHeight)
{
	m_transformMatrices.projection = glm::perspective(FOV, (float)windowWidth / windowHeight, 0.1f, RENDER_DISTANCE);
	m_transformMatrices.view = m_fps->ViewMatrix();
}
void RoboEngine::CompileShaders(void)
{
	std::vector<std::string> locations = {"aM_vertexPosition", "aM_vertexColor"};
	m_shaders.Compile();
	m_shaders.Link(locations);
}
void RoboEngine::GetUniformLocations(void) 
{
	m_uniformLocations.m_uniLocProjection = glGetUniformLocation(m_shaders.ProgramID(), "u_projectionMatrix");
	m_uniformLocations.m_uniLocView = glGetUniformLocation(m_shaders.ProgramID(), "u_viewMatrix");
	m_uniformLocations.m_uniLocModel = glGetUniformLocation(m_shaders.ProgramID(), "u_modelMatrix");
	m_uniformLocations.m_uniLocLightPosition = glGetUniformLocation(m_shaders.ProgramID(), "u_lightPosition");
	m_uniformLocations.m_uniLocEyePosition = glGetUniformLocation(m_shaders.ProgramID(), "u_eyePosition");
}
void RoboEngine::UpdateMatrices(void)
{
	m_transformMatrices.view = m_fps->ViewMatrix();
}