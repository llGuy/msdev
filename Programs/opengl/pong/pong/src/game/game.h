#ifndef GAME_HEADER
#define GAME_HEADER

#include "..\shader\shprogram.h"
#include "..\shape\ball.h"

#include <glm\gtx\transform.hpp>

class Game
{
public:
	explicit Game(void)
		: m_program("res\\vsh.shader",
			"res\\fsh.shader")
	{
	}
	void Init(unsigned int width, unsigned int height)
	{
		m_ball = new Ball(RED);

		m_program.Compile();
		m_program.Link();

		m_worldToViewProjectionMatrix = glm::perspective(glm::radians(60.0f), (float)width / height, 0.1f, 30.0f);
	}
public:
	void Draw(void)
	{
		unsigned int location = glGetUniformLocation(m_program.ProgramID(), "transformMatrix");
		m_ball->Draw(m_worldToViewProjectionMatrix, location);
	}
private:
	SHProgram m_program;
	Shape* m_ball;

	glm::mat4 m_worldToViewProjectionMatrix;
};

#endif