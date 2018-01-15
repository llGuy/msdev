#ifndef ENTITY_HEADER
#define ENTITY_HEADER

#include <glm/glm.hpp>

struct Time;
struct UniformLocations;

class Terrain;
class FPSPlayer;

class Entity
{
public:
	virtual const glm::vec3& Position(void) = 0;
	virtual const glm::vec3& ViewDirection(void) = 0;

	virtual const bool Draw(glm::mat4& proj, glm::mat4& view,
		glm::vec3& eyePos, glm::vec3& lightPos, UniformLocations* locations,
		Time* timeData, Terrain* terrain, FPSPlayer* player) {}

	// for the robot
	virtual void Move(const glm::vec3& direction) {}
};

#endif