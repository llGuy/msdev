#ifndef GAME_HEADER
#define GAME_HEADER

#include "..\shaders\shprogram.h"
#include "..\shape\ball.h"

class Game
{
public:
	explicit Game(void)
		: m_shprogram("res\\vsh.shader",
					  "res\\fsh.shader")
	{
	}
public:
	void Init(void)
	{
		m_shprogram.Link();

		m_test = new Ball(glm::vec3(1.0f, 1.0f, 0.0f));
	}
	void Draw(void)
	{
		m_test->Draw(glm::mat4(1.0f));
	}
private:
	SHProgram m_shprogram;
	Shape* m_test;
};

#endif