#ifndef ENGINE_HEADER
#define ENGINE_HEADER

#include "engine_comon.h"
#include "configs/configs.h"

#include <chrono>

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
private:
	void MatricesInit(float windowWidth, float windowHeight);
	void CompileShaders(void);
	void GetUniformLocations(void);
	void UpdateMatrices(void);
	void InitializeTime(void);
	void UpdateTimeData(void);
private:
	Configs m_configurations;
	Time m_timeData;
	FPSPlayer* m_fps;
	Terrain* m_terrain;
	SHProgram* m_shaders;
	Lighting m_lighting;
	UniformLocations m_uniformLocations;
	TransformMatrices m_transformMatrices;
};

#endif