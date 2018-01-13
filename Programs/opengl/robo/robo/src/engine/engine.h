#ifndef ENGINE_HEADER
#define ENGINE_HEADER

#include "engine_comon.h"
#include "configs/configs.h"

#include <chrono>
#include <vector>

struct UniformLocations
{
	signed int m_uniLocModel;
	signed int m_uniLocProjection;
	signed int m_uniLocView;
	signed int m_uniLocLightPosition;
	signed int m_uniLocEyePosition;
	signed int m_uniLocTime;
	signed int m_uniLocLavaHeightTopPosition;
};


class RoboEngine
{
public:
	struct TransformMatrices
	{
		glm::mat4 projection;
		glm::mat4 view;
	};
	
	struct Lighting
	{
		glm::vec3 lightPosition;
	};

	explicit RoboEngine(float windowWidth, float windowHeight);
	~RoboEngine(void);
	
	void Draw(void);
	void KeyInput(GLFWwindow*);
	void MouseInput(GLFWwindow*);
	void MouseButtonInput(int button);
private:
	void MatricesInit(float windowWidth, float windowHeight);
	void CompileShaders(void);
	void GetUniformLocations(void);
	void UpdateMatrices(void);
	void InitializeTime(void);
	void UpdateTimeData(void);
	void MoveRobots(void);
	void DrawRobots(glm::mat4& proj, glm::mat4& view,
		glm::vec3& eyePos, glm::vec3& lightPos, UniformLocations* locations, Time* time);
	void InitRobots(void);
	void SpawnRobot(void);
	const bool AllRobotsDied(void);
	void ResurectRobots(void);
private:
	Configs m_configurations;
	Time m_timeData;
	FPSPlayer* m_fps;
	Terrain* m_terrain;
	SHProgram* m_shaders;
	Lighting m_lighting;
	UniformLocations m_uniformLocations;
	TransformMatrices m_transformMatrices;

	std::vector<Robot> m_robots;
};

#endif