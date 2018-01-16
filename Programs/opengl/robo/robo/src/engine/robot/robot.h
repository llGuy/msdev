#ifndef ROBOT_HEADER
#define ROBOT_HEADER

#include <glm/glm.hpp>

#include "../../buffer/buffer.h"
#include "../data/index_data.h"
#include "../data/vertex_data.h"
#include "../shape/cube.h"
#include "../entities/entity.h"

struct Time;
struct UniformLocations;
class FPSPlayer;
class Terrain;
class Gun;

class Robot final
	: public Entity
{
public:
	explicit Robot(float radius, glm::vec2 plainPosition,
		glm::vec3 color = glm::vec3(0.0f / 255.0f, 191.0f / 255.0f, 255.0f / 255.0f));		//the robot is a cube
public:
	const bool Draw(glm::mat4& proj, glm::mat4& view,
		glm::vec3& eyePos, glm::vec3& lightPos, UniformLocations* locations,
		Time* timeData, Terrain* terrain, Entity* player) override;
	//glm::vec2& PlainPosition(void) override;
	/*void MoveTowardsPlayer(glm::vec2 playerPosition);
	void UpdateTranslateMatrix(float height);
	const bool DetectCollision(glm::vec3 bullet, float bulletRadius);*/
	/*const bool Alive(void);
	void RemoveLife(void);
	void DeleteBuffers(void);*/

	//new 
	void Move(const move_t&& movement, const glm::vec2& playerPlainPos) override;
	const bool DetectBulletCollision(const glm::vec3& worldCoords,
		const float& circleRad) override;
	const bool Alive(void) override;
	void DeleteBuffers(void) override;
	void RemoveLife(void) override;
	void UpdTransMat(const float& terrHeight) override;
	glm::vec2 PlainPosition(void) override;
	void Power(const power_t&& power, const glm::vec3& playerPos) override;
	glm::vec3 Position(void) override;
	//not new
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