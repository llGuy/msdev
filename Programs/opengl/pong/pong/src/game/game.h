#ifndef GAME_HEADER
#define GAME_HEADER

#include "..\shader\shprogram.h"
#include "..\shape\ball.h"

class Game
{
public:
	explicit Game(void)
		: m_program("res\\vsh.shader",
			"res\\fsh.shader")
	{
	}
	void Init(void)
	{
		m_ball = new Ball();

		m_program.Compile();
		m_program.Link();
	}
public:
	void Draw(void)
	{
		m_ball->Draw();
	}
private:
	SHProgram m_program;
	Shape* m_ball;
};

#endif