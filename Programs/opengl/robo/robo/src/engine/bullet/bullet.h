#ifndef Bullet_HEADER
#define Bullet_HEADER

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../primitives/vertex.h"
#include "../../buffer/buffer.h"
#include "../data/index_data.h"
#include "../data/vertex_data.h"

struct Time;
struct UniformLocations;

class Bullet
{
public:
	explicit Bullet(glm::vec3 playerViewDirection,
		glm::vec3 playerEyePos);
	~Bullet(void);

	void Draw(glm::mat4& proj, glm::mat4& view, glm::vec3& eyePos,
		glm::vec3& lightPos, UniformLocations* locations, Time* time);
	glm::vec2 PlainPosition(void);
	void Move(void);
	void UpdateTranslateMatrix(void);
	const bool CollisionCheck(float heightOfTerrain);
	const bool EscapedTerrainLimits(float x, float y);
	void DeleteBuffer(void);
private:
	void Init(glm::vec3& playerViewDirection,
		glm::vec3 playerEyePos);
	void CreateVertices(void);
	void CreateIndices(void);
	void CreateBuffer(void);
	void SendUnifromData(glm::mat4 proj, glm::mat4 view, glm::mat4 model,
		glm::vec3 eyePos, glm::vec3 lightPos, UniformLocations* locations, Time* time);
private:
	float m_cubeRadius;			//bullet is a cube like the robot
	float m_bulletSpeed;
	VertexData m_vertexData;
	IndexData m_indexData;
	Buffer m_buffer;
	glm::vec2 m_translateVectorPlainPosition;
	glm::vec3 m_worldCoordinates;
	glm::mat4 m_translateMatrix;
	glm::vec3 m_direction;
};

#endif