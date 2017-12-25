#ifndef SNAKE_HEADER
#define SNAKE_HEADER

#include <vector>
#include <math.h>

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
	explicit Snake(float speed)
		: m_xzDirectionOfSnake(1.0f, 0.0f, 0.0f), 
		m_xyzDirectionOfSnake(1.0f, 0.0f, 0.0f), m_isChangingDirection(false),
		m_colorDelta(0.05f, 0.05f, 0.05f), m_indexRightVectors(0), m_indexLeftVectors(0),
		m_isMovingInAltitude(false), m_speed(speed)
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
			CreateRightChangingPoint();
			MoveRight(m_topRightChangingPoints);
			//std::cout << "going to right" << std::endl;
		}
		if (movement == MOVE_LEFT)
		{
			CreateLeftChangingPoint();
			MoveLeft(m_topRightChangingPoints);
			//std::cout << "going to left" << std::endl;
		}
		if (movement == MOVE_UP)
		{
			CreateRightChangingPoint();
			MoveUp(m_topRightChangingPoints);
			//std::cout << "going to up" << std::endl;
		}
		if (movement == MOVE_DOWN)
		{
			CreateRightChangingPoint();
			MoveDown(m_topRightChangingPoints);
			//	std::cout << "going to down" << std::endl;
		}
	}
private:
	void AddCube(void)
	{
		Color color(GREEN);
		color.m_colorFB -= m_colorDelta;
		color.m_colorPs -= m_colorDelta;
		color.m_colorSs -= m_colorDelta;

		m_cubes.push_back(new Cube(color, 0.5f, m_xyzDirectionOfSnake, 
			*m_cubes[m_cubes.size() - 1]->TranslateVector() - m_xyzDirectionOfSnake, m_speed));
		m_colorDelta += 0.05f;
	}
	void MoveRight(glm::vec3 topRightChangingPoints[])
	{
		m_xzDirectionOfSnake = m_turningRightVectors[m_indexRightVectors];
		m_xyzDirectionOfSnake = m_xzDirectionOfSnake;
		
		for (auto& iterator : m_cubes)
			iterator->ToggleChangingDirection(m_xyzDirectionOfSnake, topRightChangingPoints[m_indexRightVectors]);
		++m_indexRightVectors;
		m_indexLeftVectors = 4 - m_indexRightVectors;
		if (m_indexRightVectors == 4)
			m_indexRightVectors = 0;
		m_isMovingInAltitude = false;
	}
	void MoveLeft(glm::vec3 topRightChangingPoints[])
	{
		m_xzDirectionOfSnake = m_turningLeftVectors[m_indexLeftVectors];
		m_xyzDirectionOfSnake = m_xzDirectionOfSnake;

		for (auto& iterator : m_cubes)
			iterator->ToggleChangingDirection(m_xyzDirectionOfSnake, topRightChangingPoints[m_indexLeftVectors]);
		++m_indexLeftVectors;
		m_indexRightVectors = 4 - m_indexLeftVectors;
		if (m_indexLeftVectors == 4)
			m_indexLeftVectors = 0;
		m_isMovingInAltitude = false;
	}
	void MoveUp(glm::vec3 topRightChangingPoints[])
	{
		m_xyzDirectionOfSnake = glm::vec3(0.0f, 1.0f, 0.0f);

		for (auto& iterator : m_cubes)
			iterator->ToggleChangingDirection(m_xyzDirectionOfSnake, topRightChangingPoints[m_indexRightVectors]);

		m_isMovingInAltitude = true;
	}
	void MoveDown(glm::vec3 topRightChangingPoints[])
	{
		m_xyzDirectionOfSnake = glm::vec3(0.0f, -1.0f, 0.0f);

		for (auto& iterator : m_cubes)
			iterator->ToggleChangingDirection(m_xyzDirectionOfSnake, topRightChangingPoints[m_indexRightVectors]);
		m_isMovingInAltitude = true;
	}
	const bool Vect3HasNegativeNumber(glm::vec3 vec, unsigned int* index)
	{
		if (vec.x < 0.0f || vec.y < 0.0f || vec.z < 0.0f)
			return true;
		return false;
	}
	void CreateRightChangingPoint(void)
	{
		m_topRightChangingPoints[0] = glm::vec3(ceil(m_cubes[0]->ShapeVerts().m_right),
			m_cubes[0]->ShapeVerts().m_top,
			m_cubes[0]->ShapeVerts().m_front);
		m_topRightChangingPoints[1] = glm::vec3(m_cubes[0]->ShapeVerts().m_right,
			m_cubes[0]->ShapeVerts().m_top,
			ceil(m_cubes[0]->ShapeVerts().m_front));
		m_topRightChangingPoints[2] = glm::vec3(floor(m_cubes[0]->ShapeVerts().m_right),
			m_cubes[0]->ShapeVerts().m_top,
			m_cubes[0]->ShapeVerts().m_front);
		m_topRightChangingPoints[3] = glm::vec3(m_cubes[0]->ShapeVerts().m_right,
			m_cubes[0]->ShapeVerts().m_top,
			floor(m_cubes[0]->ShapeVerts().m_front));

		if (m_isMovingInAltitude)
		{
			for (unsigned short iter = 0; iter < 4; ++iter)
			{
				float yVal = ceil(fabs(m_cubes[0]->ShapeVerts().m_top)) *
					m_topRightChangingPoints[iter].y / fabs(m_topRightChangingPoints[iter].y);
				m_topRightChangingPoints[iter].y = yVal;
			}
		}
	}
	void CreateLeftChangingPoint(void)
	{
		m_topRightChangingPoints[0] = glm::vec3(ceil(m_cubes[0]->ShapeVerts().m_right),
			m_cubes[0]->ShapeVerts().m_top,
			m_cubes[0]->ShapeVerts().m_front);
		m_topRightChangingPoints[1] = glm::vec3(m_cubes[0]->ShapeVerts().m_right,
			m_cubes[0]->ShapeVerts().m_top,
			floor(m_cubes[0]->ShapeVerts().m_front));
		m_topRightChangingPoints[2] = glm::vec3(floor(m_cubes[0]->ShapeVerts().m_right),
			m_cubes[0]->ShapeVerts().m_top,
			m_cubes[0]->ShapeVerts().m_front);
		m_topRightChangingPoints[3] = glm::vec3(m_cubes[0]->ShapeVerts().m_right,
			m_cubes[0]->ShapeVerts().m_top,
			ceil(m_cubes[0]->ShapeVerts().m_front));

		if (m_isMovingInAltitude)
		{
			for (unsigned short iter = 0; iter < 4; ++iter)
			{
				m_topRightChangingPoints[iter].y = ceil(fabs(m_cubes[0]->ShapeVerts().m_top)) *
					m_topRightChangingPoints[iter].y / fabs(m_topRightChangingPoints[iter].y);
			}
		}
	}
private:
	void Init(void)
	{
		m_cubes.push_back(new Cube(GREEN, 0.5f, m_xzDirectionOfSnake, glm::vec3(0.0f, 0.0f, -10.0f), m_speed));
		AddCube();
		AddCube();
		AddCube();
		
		m_turningRightVectors[0] = glm::vec3(0.0f, 0.0f, 1.0f);
		m_turningRightVectors[1] = glm::vec3(-1.0f, 0.0f, 0.0f);
		m_turningRightVectors[2] = glm::vec3(0.0f, 0.0f, -1.0f);
		m_turningRightVectors[3] = glm::vec3(1.0f, 0.0f, 0.0f);

		m_turningLeftVectors[0] = glm::vec3(0.0f, 0.0f, -1.0f);
		m_turningLeftVectors[1] = glm::vec3(-1.0f, 0.0f, 0.0f);
		m_turningLeftVectors[2] = glm::vec3(0.0f, 0.0f, 1.0f);
		m_turningLeftVectors[3] = glm::vec3(1.0f, 0.0f, 0.0f);
	}
	float Normal(float f)
	{
		return f;
	}
private:
	std::vector<Shape*> m_cubes;

	glm::vec3 m_xzDirectionOfSnake;			//if the snake is going up, the direction of the snake before is saved here
	glm::vec3 m_xyzDirectionOfSnake;		

	glm::vec3 m_colorDelta;
	const unsigned short m_headCube = 0;
	bool m_isChangingDirection;
	glm::vec3 m_topRightOfCubesChangingPoint;

	glm::vec3 m_turningRightVectors[4];
	glm::vec3 m_turningLeftVectors[4];
	glm::vec3 m_topRightChangingPoints[4];
	unsigned short m_indexRightVectors;
	unsigned short m_indexLeftVectors;

	bool m_isMovingInAltitude;
	float m_speed;
};

#endif