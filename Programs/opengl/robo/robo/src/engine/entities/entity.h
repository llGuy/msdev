#ifndef ENTITY_HEADER
#define ENTITY_HEADER

#include <vector>
#include <glm/glm.hpp>

struct Time;
struct UniformLocations;

class Terrain;
class FPSPlayer;

class Entity
{
public:
	/*	the player moves forward or backward
		the robot only moves towards the player */
	enum class move_t
	{
		FORWARD,

		BACKWARD,

		TO_PLAYER
	};
	/*	for the player	*/
	enum class strafe_t
	{
		RIGHT,

		LEFT
	};
	/*	for the player who has powers like flourish or boost...	*/
	enum class power_t
	{
		FLOURISH,

		BOOST,

		JUMP,

		TROOP,

		SHOOT
	};

	virtual glm::vec2 PlainPosition(void) { return glm::vec2(); }
	virtual glm::vec3* ViewDirection(void) { return nullptr; }
	virtual glm::vec3 Position(void) { return glm::vec3(); }
	virtual const glm::mat4 ViewMatrix(Terrain* terr, Time* time) { return glm::mat4(); }
	virtual void UpdTransMat(const float& terrHeight) {}
	virtual void UpdData(Terrain* terrain, Time* time) {}

	virtual const bool Draw(glm::mat4& proj, glm::mat4& view,
		glm::vec3& eyePos, glm::vec3& lightPos, UniformLocations* locations,
		Time* timeData, Terrain* terrain, Entity* player) { return false; }
	virtual const bool Draw(glm::mat4& proj, glm::mat4& view,
		glm::vec3& eyePos, glm::vec3& lightPos, UniformLocations* locations,
		Time* timeData, Terrain* terrain, std::vector<Entity*>& robots) { return false; }
	virtual void DrawBullets(glm::mat4& proj, glm::mat4& view, glm::vec3& eyePos,
		glm::vec3& lightPos, UniformLocations* locations, Time* time, 
		Terrain* terrain, std::vector<Entity*>& vec) {}
	virtual void DrawBullets(glm::mat4& proj, glm::mat4& view, glm::vec3& eyePos,
		glm::vec3& lightPos, UniformLocations* locations, Time* time, 
		Terrain* terrain, Entity*) {} // this function is for the robots when they shoot the player
	virtual void DrawTroops(glm::mat4& proj, glm::mat4& view,
		glm::vec3& eyePos, glm::vec3& lightPos, UniformLocations* locations,
		Time* timeData, Terrain* terrain, std::vector<Entity*>& robots) {}

	virtual void Move(const move_t&& movement, const float& terrHeight,
		const glm::vec3& direction = glm::vec3(0.0f)) {}
	virtual void Move(const move_t&& movement, const glm::vec2& playerPlainPos) {}
	virtual void Strafe(const strafe_t&& strafe, const float& terrHeight) {}
	virtual void Power(const power_t&& power, const glm::vec3& playerPos = glm::vec3(0.0f)) {}
	virtual void Power(const power_t&& power, const std::vector<Entity*>& robots) {}
	virtual void DisablePower(const power_t&& power) {}
	virtual void EnablePower(const power_t&& power) {}

	// for the bullets
	virtual const bool DetectBulletCollision(const glm::vec3& worldCoords, 
		const float& circleRad) { return false; }
	virtual const bool Alive(void) { return false; }
	virtual void DeleteBuffers(void) {}
	virtual void RemoveLife(void) {}

	// for the player
	virtual bool* Running(void) { return nullptr; }
	virtual void SpeedUp(void) {}
	virtual void NeutralizeSpeed(const float& speed) {}
	virtual const bool BulletAiring(void) { return false; }
	virtual void ViewBob(void) {}
};

#endif