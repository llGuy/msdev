#ifndef ROBOT_HEADER
#define ROBOT_HEADER

#include <glm/glm.hpp>

#include "../../buffer/buffer.h"
#include "../data/index_data.h"
#include "../data/vertex_data.h"

struct Time;
struct UniformLocations;

class Robot
{
public:
	explicit Robot(float radius);		//the robot is a cube
public:
	void Draw(glm::mat4& proj, glm::mat4& view, 
		glm::vec3& eyePos, glm::vec3& lightPos, UniformLocations* locations, Time* timeData);
	glm::vec2 PlainPosition(void);
	void MoveTowardsPlayer(glm::vec2 playerPosition);
	void UpdateTranslateMatrix(float height);
private:
	void SendUniformData(glm::mat4& proj, glm::mat4& view, glm::mat4& model, 
		glm::vec3& eyePos, glm::vec3& lightPos, UniformLocations* locations, Time* time);
	void CreateVertices(void);
	void CreateIndices(void);
	void InitBuffer(void);
private:
	VertexData m_vertexData;
	IndexData m_indexData;
	Buffer m_buffer;
	glm::vec2 m_translateVectorPlainPosition;
	glm::vec3 m_worldCoordinates;
	glm::mat4 m_translateMatrix;
	float m_cubeRadius;
	float m_robotSpeed;
	glm::vec2 m_viewDirection;
};

#endif