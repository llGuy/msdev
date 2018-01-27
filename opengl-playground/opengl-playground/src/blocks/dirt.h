#ifndef DIRT_HEADER
#define DIRT_HEADER

#include "block.h"

#include <glm/gtx/transform.hpp>

class Dirt_Block
	: public Block
{
public:
	explicit Dirt_Block(const glm::vec3& position)
	{
		m_translateMatrix = glm::translate(position);
		m_texture = Texture(Block::DIRT);
		m_cube = Cube(0.5f);
	}
	void Draw(glm::mat4& proj, glm::mat4& view,
		glm::vec3& eyePosition, glm::vec3& lightPosition, UniformLocations* locations) override
	{
		m_texture.Bind(0);
		UniformData(locations, proj, view, m_translateMatrix, eyePosition, lightPosition);
		m_cube.Draw(proj, view, m_translateMatrix, eyePosition, lightPosition, locations);
	}
	void Draw(glm::mat4& proj, glm::mat4& view, glm::mat4& model,
		glm::vec3& eyePosition, glm::vec3& lightPosition, UniformLocations* locations)
	{
		m_texture.Bind(0);
		UniformData(locations, proj, view, model, eyePosition, lightPosition);
		m_cube.Draw(proj, view, model, eyePosition, lightPosition, locations);
	}
	void Init(void) override
	{
		m_texture.Init();
	}
private:
	void UniformData(UniformLocations* loc, glm::mat4& proj, glm::mat4& view, glm::mat4& model,
		glm::vec3& eyePosition, glm::vec3& lightPosition)
	{
		glUniformMatrix4fv(loc->m_uniLocProjection, 1, GL_FALSE, &proj[0][0]);
		glUniformMatrix4fv(loc->m_uniLocView, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(loc->m_uniLocModel, 1, GL_FALSE, &model[0][0]);
		glUniform3fv(loc->m_uniLocLightPosition, 1, &lightPosition[0]);
		glUniform3fv(loc->m_uniLocEyePosition, 1, &eyePosition[0]);
	}
};

#endif