#ifndef HANDLER_HEADER
#define HANDLER_HEADER

#include <vector>

#include "stone.h"
#include "dirt.h"
#include "dore.h"
#include "../shader/shprogram.h"

class BlockHandler
{
public:
	explicit BlockHandler(void)
		: m_program("res\\blocks\\vsh.shader", "res\\blocks\\fsh.shader", "res\\blocks\\gsh.shader")
	{
		glm::vec3 position = glm::vec3(0.0f, 10.0f, 0.0f);
		m_program.Compile();
		std::vector<const char*> vec = { "aM_vertexPosition", "aM_textCoords" };
		m_program.Link(vec);
		m_blocks.push_back(new Stone_Block(position));
		m_blocks.push_back(new Dirt_Block(position));
		m_blocks.push_back(new Dore_Block(position));
		m_blocks[0]->Init();
		m_blocks[1]->Init();
		m_blocks[2]->Init();
		GetUniformLocations();

		for (unsigned int i = 0; i < 20; i++)
		{
			glm::vec3 randomPosition;
			randomPosition.x = rand() % 25 - 12.5f;
			randomPosition.y = 20.0f;
			randomPosition.z = rand() % 25 - 12.5f;

			m_randomPositionsStone[i] = randomPosition;
		}
		for (unsigned int i = 0; i < 20; i++)
		{
			glm::vec3 randomPosition;
			randomPosition.x = rand() % 25 - 12.5f;
			randomPosition.y = 18.0f;
			randomPosition.z = rand() % 25 - 12.5f;

			m_randomPositionsDirt[i] = randomPosition;
		}
		for (unsigned int i = 0; i < 20; i++)
		{
			glm::vec3 randomPosition;
			randomPosition.x = rand() % 25 - 12.5f;
			randomPosition.y = 17.0f;
			randomPosition.z = rand() % 25 - 12.5f;

			m_randomPositionsDore[i] = randomPosition;
		}
	}
	void Draw(glm::mat4& proj, glm::mat4& view, glm::vec3& eyePos, glm::vec3& lightPos)
	{
		m_program.UseProgram();
		m_blocks[0]->Draw(proj, view, eyePos, lightPos, &m_locations);

		for (unsigned int i = 0; i < 20; i++)
		{
			glm::mat4 translate = glm::translate(m_randomPositionsStone[i]);
			m_blocks[0]->Draw(proj, view, translate, eyePos, lightPos, &m_locations);
		}
		for (unsigned int i = 0; i < 20; i++)
		{
			glm::mat4 translate = glm::translate(m_randomPositionsDirt[i]);
			m_blocks[1]->Draw(proj, view, translate, eyePos, lightPos, &m_locations);
		}
		for (unsigned int i = 0; i < 20; i++)
		{
			glm::mat4 translate = glm::translate(m_randomPositionsDore[i]);
			m_blocks[2]->Draw(proj, view, translate, eyePos, lightPos, &m_locations);
		}
	}
private:
	void GetUniformLocations(void)
	{
		m_locations.m_uniLocProjection = glGetUniformLocation(m_program.ProgramID(), "u_projectionMatrix");
		m_locations.m_uniLocView = glGetUniformLocation(m_program.ProgramID(), "u_viewMatrix");
		m_locations.m_uniLocModel = glGetUniformLocation(m_program.ProgramID(), "u_modelMatrix");
		m_locations.m_uniLocLightPosition = glGetUniformLocation(m_program.ProgramID(), "u_lightPosition");
		m_locations.m_uniLocEyePosition = glGetUniformLocation(m_program.ProgramID(), "u_eyePosition");
	}
private:
	std::vector<Block*> m_blocks;
	UniformLocations m_locations;
	SHProgram m_program;

	glm::vec3 m_randomPositionsStone[20];
	glm::vec3 m_randomPositionsDirt[20];
	glm::vec3 m_randomPositionsDore[20];
};

#endif