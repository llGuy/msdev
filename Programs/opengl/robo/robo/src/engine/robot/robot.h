#ifndef ROBOT_HEADER
#define ROBOT_HEADER

#include <glm/glm.hpp>

#include "../../buffer/buffer.h"
#include "../data/index_data.h"
#include "../data/vertex_data.h"
#include "../shape/cube.h"

struct Time;
struct UniformLocations;
class FPSPlayer;
class Terrain;
class Gun;

class Robot
{
public:
	explicit Robot(float radius, glm::vec2 plainPosition,
		glm::vec3 color = glm::vec3(0.0f / 255.0f, 191.0f / 255.0f, 255.0f / 255.0f));		//the robot is a cube
public:
	const bool Draw(glm::mat4& proj, glm::mat4& view, 
		glm::vec3& eyePos, glm::vec3& lightPos, UniformLocations* locations, Time* timeData, Terrain* terrain, FPSPlayer* player);
	glm::vec2 PlainPosition(void);
	void MoveTowardsPlayer(glm::vec2 playerPosition);
	void UpdateTranslateMatrix(float height);
	const bool DetectCollision(glm::vec3 bullet, float bulletRadius);
	const bool Alive(void);
	void RemoveLife(void);
	void DeleteBuffers(void);
private:
	void SendUniformData(glm::mat4& proj, glm::mat4& view, glm::mat4& model, 
		glm::vec3& eyePos, glm::vec3& lightPos, UniformLocations* locations, Time* time);
	void RobotDataInit(void);
	const bool WantsToShoot(void);
	void Shoot(glm::vec3 playerPosition);
private:	
	Shape* m_cube;
	Gun* m_gun;
	glm::vec2 m_translateVectorPlainPosition;
	glm::vec3 m_worldCoordinates;
	glm::mat4 m_translateMatrix;
	float m_cubeRadius;
	float m_circleRadius;
	float m_robotSpeed;
	glm::vec2 m_viewDirection;
	unsigned int m_lives;
	bool m_hitPlayer;
};

#endif