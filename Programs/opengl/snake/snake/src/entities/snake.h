#ifndef SNAKE_HEADER
#define SNAKE_HEADER

#include <vector>

#include "..\shape\cube.h"

class Snake
{
public:
	enum movement_t
	{	
		MOVE_LEFT,

		MOVE_RIGHT,

		MOVE_UP,

		MOVE_DOWN
	};
	explicit Snake(void)
		: m_colorDelta(0.0f, 0.0f, 0.0f), m_xzDirectionOfSnake(1.0f, 0.0f, 0.0f), m_xyzDirectionOfSnake(1.0f, 0.0f, 0.0f)
	{
		Init();
	}
public:
	void Draw(glm::mat4 viewProjectionMatrix, unsigned int location)
	{
		for (auto& cubeIter : m_cubes)
			cubeIter->Move();
		for (auto& cubeIter : m_cubes)
			cubeIter->Draw(viewProjectionMatrix, location);
	}
	Shape* Head(void)
	{
		return m_cubes[m_headCube];
	}
	void Move(movement_t movement)
	{
		if (movement == MOVE_RIGHT)
		{
			MoveRight();
		}
		if (movement == MOVE_LEFT)
		{
			MoveLeft();
		}
		if (movement == MOVE_UP)
		{
			MoveUp();
		}
		if (movement == MOVE_DOWN)
		{
			MoveDown();
		}
	}
	void MoveRight(void)
	{
		if (fabs(m_xzDirectionOfSnake.x - 1.0f) < 0.001f)
		{
			m_xzDirectionOfSnake = glm::vec3(0.0f, 0.0f, 1.0f);
		}
		else if (fabs(m_xzDirectionOfSnake.z - 1.0f) < 0.001f)
		{
			m_xzDirectionOfSnake = glm::vec3(-1.0f, 0.0f, 0.0f);
		}
		else if (fabs(m_xzDirectionOfSnake.x + 1.0f) < 0.001f)
		{
			m_xzDirectionOfSnake = glm::vec3(0.0f, 0.0f, -1.0f);
		}
		else if (fabs(m_xzDirectionOfSnake.z + 1.0f) < 0.001f)
		{
			m_xzDirectionOfSnake = glm::vec3(1.0f, 0.0f, 0.0f);
		}
		m_xyzDirectionOfSnake = m_xzDirectionOfSnake;
		for (auto& iterator : m_cubes)
			iterator->ChangeDirection(m_xyzDirectionOfSnake);
	}
	void MoveLeft(void)
	{
		if (fabs(m_xzDirectionOfSnake.x - 1.0f) < 0.001f)
		{
			m_xzDirectionOfSnake = glm::vec3(0.0f, 0.0f, -1.0f);
		}
		else if (fabs(m_xzDirectionOfSnake.z - 1.0f) < 0.001f)
		{
			m_xzDirectionOfSnake = glm::vec3(1.0f, 0.0f, 0.0f);
		}
		else if (fabs(m_xzDirectionOfSnake.x + 1.0f) < 0.001f)
		{
			m_xzDirectionOfSnake = glm::vec3(0.0f, 0.0f, 1.0f);
		}
		else if (fabs(m_xzDirectionOfSnake.z + 1.0f) < 0.001f)
		{
			m_xzDirectionOfSnake = glm::vec3(-1.0f, 0.0f, 0.0f);
		}
		m_xyzDirectionOfSnake = m_xzDirectionOfSnake;
		for (auto& iterator : m_cubes)
			iterator->ChangeDirection(m_xyzDirectionOfSnake);
	}
	void MoveUp(void)
	{
		m_xyzDirectionOfSnake = glm::vec3(0.0f, 1.0f, 0.0f);
		for (auto& iterator : m_cubes)
			iterator->ChangeDirection(m_xyzDirectionOfSnake);
	}
	void MoveDown(void)
	{
		m_xyzDirectionOfSnake = glm::vec3(0.0f, -1.0f, 0.0f);
		for (auto& iterator : m_cubes)
			iterator->ChangeDirection(m_xyzDirectionOfSnake);
	}
private:
	void Init(void)
	{
		m_cubes.push_back(new Cube(GREEN, 0.5f, m_xzDirectionOfSnake));
	}
private:
	std::vector<Shape*> m_cubes;

	glm::vec3 m_colorDelta;
	glm::vec3 m_xzDirectionOfSnake;			//if the snake is going up, the direction of the snake before is saved here
	glm::vec3 m_xyzDirectionOfSnake;		

	const unsigned short m_headCube = 0;
};

#endif