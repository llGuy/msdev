#include "engine.h"

#include <GL/glew.h>

RoboEngine::RoboEngine(float windowWidth, float windowHeight)
	: m_lighting({ glm::vec3(0.0f, 100.0f, 0.0f) })
{ 
	
	m_terrain = new Terrain({ m_configurations.terrainWidth, m_configurations.terrainDepth, m_configurations.terrainMaxHeight }, Biome::VOLCANO);
	m_fps = new FPSPlayer({ glm::vec3(m_configurations.originalPlayerPosition.x,
		m_terrain->GetYPosOfPlayer(m_configurations.originalPlayerPosition.x, m_configurations.originalPlayerPosition.z), m_configurations.originalPlayerPosition.z),
		m_configurations.originalPlayerViewDirection, m_configurations.playerSpeed, m_configurations.playerHeight, m_configurations.playerViewBobbing,
		m_configurations.playerRunningSpeedDelta});
	
	InitRobots();

	if (m_terrain->BiomeType() == Biome::VOLCANO) m_shaders = new SHProgram("res\\lavaVsh.shader", "res\\lavaFsh.shader", "res\\lavaGsh.shader");
	else m_shaders = new SHProgram("res\\vsh.shader", "res\\fsh.shader", "res\\gsh.shader");

	MatricesInit(windowWidth, windowHeight);
	CompileShaders();
	GetUniformLocations();
	InitializeTime();
}
RoboEngine::~RoboEngine(void)
{
}
void RoboEngine::Draw(void)
{
	glm::vec3 m_skyColor = m_terrain->Sky();
	glClearColor(m_skyColor.r, m_skyColor.g, m_skyColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	UpdateMatrices();
	UpdateTimeData();
	MoveRobots();
	m_shaders->UseProgram();
	if (m_fps->BulletAiring())
		m_fps->DrawBullets(m_transformMatrices.projection, m_transformMatrices.view, 
			m_fps->Position(), m_lighting.lightPosition, &m_uniformLocations, &m_timeData, m_terrain, m_robots);
	DrawRobots(m_transformMatrices.projection, m_transformMatrices.view, m_fps->Position(), m_lighting.lightPosition, &m_uniformLocations, &m_timeData);
	m_terrain->Draw(m_transformMatrices.projection, m_transformMatrices.view, m_fps->Position(), m_lighting.lightPosition, &m_uniformLocations, &m_timeData);
}
void RoboEngine::KeyInput(GLFWwindow* window)
{
	bool movement = false;
	if (m_fps->Running())
	{
		m_fps->NormalSpeed(m_configurations.playerSpeed);
		m_fps->Running() = false;
	}
	if (glfwGetKey(window, GLFW_KEY_R))
	{
		m_fps->Running() = true;
		m_fps->SpeedUp();
	}
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		m_fps->Move(FPSPlayer::FORWARD, m_terrain->GetYPosOfPlayer(m_fps->Position().x, m_fps->Position().z));
		movement = true;
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		m_fps->Move(FPSPlayer::BACKWARD, m_terrain->GetYPosOfPlayer(m_fps->Position().x, m_fps->Position().z));
		movement = true;
	}
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		m_fps->Strafe(FPSPlayer::LEFT, m_terrain->GetYPosOfPlayer(m_fps->Position().x, m_fps->Position().z));
		movement = true;
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		m_fps->Strafe(FPSPlayer::RIGHT, m_terrain->GetYPosOfPlayer(m_fps->Position().x, m_fps->Position().z));
		movement = true;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE))
	{
		m_fps->InitializeJump(m_timeData.deltaT);
	}
	if (movement)
	{
		m_fps->ViewBobbing();
	}
}
void RoboEngine::MouseInput(GLFWwindow* window)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	m_fps->Look(glm::vec2(x, y));
}
void RoboEngine::MouseButtonInput(int button)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		m_fps->Shoot();
	}
}
void RoboEngine::MatricesInit(float windowWidth, float windowHeight)
{
	m_transformMatrices.projection = glm::perspective(m_configurations.fov, (float)windowWidth / windowHeight, 0.1f, m_configurations.renderDistance);
	m_transformMatrices.view = m_fps->ViewMatrix(m_terrain->GetYPosOfPlayer(m_fps->Position().x, m_fps->Position().z), &m_timeData);
}
void RoboEngine::CompileShaders(void)
{
	std::vector<std::string> locations = {"aM_vertexPosition", "aM_vertexColor"};
	m_shaders->Compile();
	m_shaders->Link(locations);
}
void RoboEngine::GetUniformLocations(void) 
{
	m_uniformLocations.m_uniLocProjection = glGetUniformLocation(m_shaders->ProgramID(), "u_projectionMatrix");
	m_uniformLocations.m_uniLocView = glGetUniformLocation(m_shaders->ProgramID(), "u_viewMatrix");
	m_uniformLocations.m_uniLocModel = glGetUniformLocation(m_shaders->ProgramID(), "u_modelMatrix");
	m_uniformLocations.m_uniLocLightPosition = glGetUniformLocation(m_shaders->ProgramID(), "u_lightPosition");
	m_uniformLocations.m_uniLocEyePosition = glGetUniformLocation(m_shaders->ProgramID(), "u_eyePosition");
	if (m_terrain->BiomeType() == Biome::VOLCANO)
	{
		m_uniformLocations.m_uniLocTime = glGetUniformLocation(m_shaders->ProgramID(), "u_time");
		m_uniformLocations.m_uniLocLavaHeightTopPosition = glGetUniformLocation(m_shaders->ProgramID(), "u_lavaHeightTop");
	}
}
void RoboEngine::UpdateMatrices(void)
{
	m_transformMatrices.view = m_fps->ViewMatrix(m_terrain->GetYPosOfPlayer(m_fps->Position().x, m_fps->Position().z), &m_timeData);
}
void RoboEngine::InitializeTime(void)
{
	m_timeData.currentTime = std::chrono::high_resolution_clock::now();
	m_timeData.beginning = std::chrono::high_resolution_clock::now();
}
void RoboEngine::UpdateTimeData(void)
{
	m_timeData.deltaT = (double)((std::chrono::high_resolution_clock::now() - m_timeData.currentTime).count()) / 1000000000;
	m_timeData.currentTime = std::chrono::high_resolution_clock::now();
}
void RoboEngine::MoveRobots(void)
{
	for (auto& iter : m_robots)
	{
		float heightOfRobot = m_terrain->GetYPosOfPlayer(iter.PlainPosition().x, iter.PlainPosition().y);
		glm::vec2 playerPlainPositions = glm::vec2(m_fps->Position().x, m_fps->Position().z);
		iter.MoveTowardsPlayer(playerPlainPositions);
		iter.UpdateTranslateMatrix(heightOfRobot);
	}
}
void RoboEngine::DrawRobots(glm::mat4& proj, glm::mat4& view,
	glm::vec3& eyePos, glm::vec3& lightPos, UniformLocations* locations, Time* time)
{
	for (auto& iter : m_robots)
	{
		iter.Draw(proj, view, eyePos, lightPos, locations, time);
	}
}
void RoboEngine::InitRobots(void)
{
	m_robots.push_back(Robot(0.5f));
}