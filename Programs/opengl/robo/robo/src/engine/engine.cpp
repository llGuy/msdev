#include "engine.h"

#include <GL/glew.h>
#include <ctime>
#include <cmath>

RoboEngine::RoboEngine(float windowWidth, float windowHeight)
	: m_lighting({ glm::vec3(0.0f, 100.0f, 0.0f) }), m_configurations()
{ 
	srand(static_cast<int>(time(NULL)));

	m_terrain = new Terrain({ m_configurations.terrainWidth, m_configurations.terrainDepth, 
		m_configurations.terrainMaxHeight }, Biome::VOLCANO);

	Configure();
	Configs& c = m_configurations;

	m_fps = new FPSPlayer({ glm::vec3(c.originalPlayerPosition.x,
		m_terrain->GetYPosOfPlayer(c.originalPlayerPosition.x, 
			c.originalPlayerPosition.z), c.originalPlayerPosition.z),
		c.originalPlayerViewDirection, c.playerSpeed, c.playerHeight, c.playerViewBobbing,
		c.playerRunningSpeedDelta});
	
	InitRobots();

	if (m_terrain->BiomeType() == Biome::VOLCANO) m_shaders = new SHProgram("..\\robo\\res\\lavaVsh.shader", 
		"..\\robo\\res\\lavaFsh.shader", "..\\robo\\res\\lavaGsh.shader");
	else m_shaders = new SHProgram("..\\robo\\res\\vsh.shader", "..\\robo\\res\\fsh.shader", "..\\robo\\res\\gsh.shader");

	MatricesInit(windowWidth, windowHeight);
	CompileShaders();
	GetUniformLocations();
	InitializeTime();
}
RoboEngine::~RoboEngine(void)
{
}
void RoboEngine::Configure(void)
{
	Configs& c = m_configurations;

	c.numberOfRobots = 10;

	c.playerSpeed = 0.02f;
	c.playerRunningSpeedDelta = 1.4f;
	c.playerViewBobbing = 0.002f;
	c.playerHeight = 1.0f;
	c.originalPlayerPosition = glm::vec3(0.0f);
	c.originalPlayerViewDirection = glm::vec3(0.0f, 0.0f, -1.0f);

	c.terrainWidth = 250.0f;
	c.terrainDepth = 250.0f;
	c.terrainMaxHeight = 100.0f;

	//perspective matrices
	c.renderDistance = 200.0f;
	c.fov = glm::radians(60.0f);

	//shader configs
	c.vsh = "res\\vsh.shader";
	c.fsh = "res\\fsh.shader";
	c.gsh = "res\\gsh.shader";

	m_skyColor.currentSkyColor = m_terrain->Sky();
	m_skyColor.defaultSkyColor = m_terrain->Sky();
	m_skyColor.playerHitColor = glm::vec3(0.8f, 0.0f, 0.0f);
	m_skyColor.resurrectColor = glm::vec3(0.0f, 0.8f, 0.0f);
	m_skyColor.timeBetweenChange = 0.2f;
}
void RoboEngine::Draw(void)
{
	glClearColor(m_skyColor.currentSkyColor.r, m_skyColor.currentSkyColor.g,
		m_skyColor.currentSkyColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (AllRobotsDied()) ResurectRobots();
	UpdateMatrices();
	UpdateTimeData();
	MoveRobots();
	m_shaders->UseProgram();
	DrawAll();
	ChangeSkyColorIfColorChangedForEnoughTime();
}
void RoboEngine::DrawAll(void)
{
	if (m_fps->BulletAiring())
	{
		m_fps->DrawBullets(m_transformMatrices.projection, m_transformMatrices.view,
			m_fps->Position(), m_lighting.lightPosition, &m_uniformLocations, &m_timeData, m_terrain, m_robots);
	}
	DrawRobots(m_transformMatrices.projection, m_transformMatrices.view, m_fps->Position(), 
		m_lighting.lightPosition, &m_uniformLocations, &m_timeData);
	m_terrain->Draw(m_transformMatrices.projection, m_transformMatrices.view, m_fps->Position(), 
		m_lighting.lightPosition, &m_uniformLocations, &m_timeData);
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
	if (glfwGetKey(window, GLFW_KEY_T))
	{
		m_fps->InitializeFlourish(m_timeData.deltaT);
		m_fps->DisableFlourish();
	}
	if (glfwGetKey(window, GLFW_KEY_B))
	{
		m_fps->InitializeBoost(m_timeData.deltaT);
		m_fps->DisableBoost();
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
	m_transformMatrices.projection = glm::perspective(m_configurations.fov, 
		(float)windowWidth / windowHeight, 0.1f, m_configurations.renderDistance);
	m_transformMatrices.view = m_fps->ViewMatrix(m_terrain, &m_timeData);
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
	m_transformMatrices.view = m_fps->ViewMatrix(m_terrain, &m_timeData);
}
void RoboEngine::InitializeTime(void)
{
	m_timeData.currentTime = std::chrono::high_resolution_clock::now();
	m_timeData.beginning = std::chrono::high_resolution_clock::now();
	m_skyColor.startOfChange = std::chrono::high_resolution_clock::now();
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
		bool changeColor = iter.Draw(proj, view, eyePos, lightPos, locations, time, m_terrain, m_fps);
		if (changeColor)
		{
			m_skyColor.currentSkyColor = m_skyColor.playerHitColor;
			m_skyColor.startOfChange = std::chrono::high_resolution_clock::now();
		}
	}
}
void RoboEngine::InitRobots(void)
{
	for(unsigned int i = 0; i < m_configurations.numberOfRobots; ++i)
		SpawnRobot();
}
void RoboEngine::SpawnRobot(void)
{
	float x = rand() % (signed int)m_configurations.terrainWidth / 2 - m_configurations.terrainWidth / 4;
	float z = rand() % (signed int)m_configurations.terrainDepth / 2 - m_configurations.terrainDepth / 4;

	//size of robot
	float radius = static_cast<float>(rand() % 20 / 4);
	radius /= 2;
	if (radius < 0.25f) radius = 0.25f;

	m_robots.push_back(Robot(radius, glm::vec2(x, z)));
}
const bool RoboEngine::AllRobotsDied(void)
{
	return m_robots.size() == 0;
}
void RoboEngine::ResurectRobots(void)
{
	m_skyColor.currentSkyColor = m_skyColor.resurrectColor;
	m_skyColor.startOfChange = std::chrono::high_resolution_clock::now();
	m_fps->EnableFlourish();
	m_fps->EnableBoost();
	m_configurations.numberOfRobots += 2;
	std::cout << "RESURRECTED THE ROBOTS!!!" << std::endl;
	for (unsigned int i = 0; i < m_configurations.numberOfRobots; ++i)
		SpawnRobot();
}
void RoboEngine::ChangeSkyColorIfColorChangedForEnoughTime(void)
{
	double duration = (double)((std::chrono::high_resolution_clock::now() - m_skyColor.startOfChange).count()) / 1000000000;
	if (duration > m_skyColor.timeBetweenChange)
		m_skyColor.currentSkyColor = m_skyColor.defaultSkyColor;
}