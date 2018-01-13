#ifndef CONFIG_HEADER
#define CONFIG_HEADER

struct Configs
{
	unsigned int numberOfRobots = 30;

	float playerSpeed = 0.02f;
	float playerRunningSpeedDelta = 1.4f;
	float playerViewBobbing = 0.002f;
	float playerHeight = 1.0f;
	glm::vec3 originalPlayerPosition = glm::vec3(0.0f);
	glm::vec3 originalPlayerViewDirection = glm::vec3(0.0f, 0.0f, -1.0f);

	float terrainWidth = 250.0f;
	float terrainDepth = 250.0f;
	float terrainMaxHeight = 100.0f;

	//perspective matrices
	float renderDistance = 200.0f;
	float fov = glm::radians(60.0f);

	//shader configs
	const char* vsh = "res\\vsh.shader";
	const char* fsh = "res\\fsh.shader";
	const char* gsh = "res\\gsh.shader";
};

#endif