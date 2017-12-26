#ifndef APPLE_HEADER
#define APPLE_HEADER

#include "..\shape\cube.h"

class Apple
{
public:
	explicit Apple(glm::vec3 translateVector)
	{
		Init();
	}
	void Draw(glm::mat4 m_projectionMatrix, unsigned int location)
	{
		m_cube->Draw(m_projectionMatrix, location);
	}
	void GenerateNewApple(void)
	{
		GenerateTranslateVector();
		*m_cube->TranslateVector() = m_translateVector;
	}
	Shape* CubeObj(void)
	{
		return m_cube;
	}
private:
	void GenerateTranslateVector(void)
	{
		srand(time(NULL));

		int m_x = rand() % 20 - 10;
		int m_y = rand() % 20 - 10;
		int m_z = rand() % 20 - 20;

		m_translateVector = (glm::vec3((float)m_x - 0.5f, (float)m_y - 0.5f, (float)m_z - 0.5f));
	}
	void Init(void)
	{
		GenerateTranslateVector();
		m_cube = new Cube(RED, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f), m_translateVector, 0.0f, false);
	}
private:
	Shape* m_cube;
	glm::vec3 m_translateVector;
};

#endif