#ifndef BLOCK_HEADER
#define BLOCK_HEADER

#include <string>
#include <glm/glm.hpp>

#include "../cube/cube.h"
#include "../texture/texture.h"

struct UniformLocations;
class Block
{
public:
	explicit Block(void) {}
	virtual void Draw(glm::mat4& proj, glm::mat4& view,
		glm::vec3& eyePosition, glm::vec3& lightPosition, UniformLocations* locations) {}
	virtual void Draw(glm::mat4& proj, glm::mat4& view, glm::mat4& model,
		glm::vec3& eyePosition, glm::vec3& lightPosition, UniformLocations* locations) {}
	virtual void Init(void) {}
protected:
	static const std::string&& STONE;
	static const std::string&& DIRT;
	static const std::string&& DORE;
protected:
	Cube m_cube;
	Texture m_texture;
	glm::mat4 m_translateMatrix;
};

#endif