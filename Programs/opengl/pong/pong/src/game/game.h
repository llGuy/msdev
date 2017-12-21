#ifndef GAME_HEADER
#define GAME_HEADER

#include "..\shader\shprogram.h"
#include "..\shape\ball.h"
#include "..\shape\paddle.h"

#include <glm\gtx\transform.hpp>
#include <vector>

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
		m_balls.push_back(new Ball(MAGENTA, 
			glm::vec3(0.0f, 0.0f, m_zValueOfAllCloseVerts), glm::vec3(1.0f, 1.0f, 0.0f),
			m_topGamePlane, m_bottomGamePlane));

		m_paddles.push_back(new Paddle(RED, glm::vec3(m_xValPaddleLeft, 0.0f, m_zValueOfAllCloseVerts)));
		m_paddles.push_back(new Paddle(BLUE, glm::vec3(m_xValPaddleRight, 0.0f, m_zValueOfAllCloseVerts)));

		m_program.Compile();
		m_program.Link();

		m_worldToViewProjectionMatrix = 
			glm::perspective(glm::radians(60.0f), (float)width / height, 0.1f, 30.0f);
	}
public:
	void Draw(void)
	{
		unsigned int location = glGetUniformLocation(m_program.ProgramID(), "transformMatrix");
		
		for (auto& ballIterator : m_balls)
			ballIterator->Draw(m_worldToViewProjectionMatrix, location, 
				&m_paddles[0]->ShapeVerts(), &m_paddles[1]->ShapeVerts());

		for (auto& paddleIterator : m_paddles)
			paddleIterator->Draw(m_worldToViewProjectionMatrix, location);
	}
	Shape*& PaddleLeft(void)
	{
		return m_paddles[0];
	}
	Shape*& PaddleRight(void)
	{
		return m_paddles[1];
	}
private:
	SHProgram m_program;

	std::vector<Shape*> m_balls;
	std::vector<Shape*> m_paddles;

	glm::mat4 m_worldToViewProjectionMatrix;

	const float m_zValueOfAllCloseVerts = -7.0f;
	const float m_xValPaddleLeft		= -4.0f;
	const float m_xValPaddleRight		= +4.0f;
	const float m_topGamePlane			= +3.399f;
	const float m_bottomGamePlane		= -3.399f;
};

#endif