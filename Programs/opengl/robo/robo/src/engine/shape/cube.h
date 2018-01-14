#ifndef CUBE_HEADER
#define CUBE_HEADER

#include "shape.h"

struct UniformLocations;
struct Time;

class Cube 
	: public Shape
{
public:
	explicit Cube(float rad, glm::vec3 color, const bool elevate);
	void Draw(glm::mat4& proj, glm::mat4& view, glm::mat4& model,
		glm::vec3& eyePos, glm::vec3& lightPos, UniformLocations* locations,
		Time* timeData) override;
	void Init(void) override;
	void DeleteBuffers(void) override;
protected:
	void VerticesInit(void) override;
	void IndicesInit(void) override;
	void BufferInit(void) override;
	void DeleteRAM(void) override;

	void UniformData(glm::mat4& proj, glm::mat4& view, glm::mat4& model,
		glm::vec3& eyePos, glm::vec3& lightPos,
		Time* timeData, UniformLocations* locations) override;
protected:
	glm::vec3 m_color;
	float m_cubeRadius;
	bool m_elevate;
};

#endif