#ifndef ENGINE_HEADER
#define ENGINE_HEADER

#include "engine_comon.h"

struct UniformLocations
{
	signed int m_uniLocModel;
	signed int m_uniLocProjection;
	signed int m_uniLocView;
	signed int m_uniLocLightPosition;
	signed int m_uniLocEyePosition;
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
private:
	const glm::vec3 ORIGINAL_FPSPLAYER_POSITION = glm::vec3(0.0f);
	const glm::vec3 ORIGINAL_FPSPLAYER_VIEW_DIRECTION = glm::vec3(0.0f, 0.0f, -1.0f);
	const float TERRAIN_X = 200.0f;
	const float TERRAIN_Z = 200.0f;
	const float TERRAIN_MAX_HEIGHT = 80.0f;
	const float RENDER_DISTANCE = 200.0f;
	const float FOV = glm::radians(60.0f);
	const char const* VSH = "res\\vsh.shader";
	const char const* FSH = "res\\fsh.shader";
	const char const* GSH = "res\\gsh.shader";

	mutable float m_playerSpeed = 0.02f;
	mutable float m_playerHeight = 0.7f;

	FPSPlayer* m_fps;
	Terrain* m_terrain;
	SHProgram m_shaders;
	Lighting m_lighting;
	UniformLocations m_uniformLocations;
	TransformMatrices m_transformMatrices;
};

#endif