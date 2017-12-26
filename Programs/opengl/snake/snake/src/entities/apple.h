#ifndef APPLE_HEADER
#define APPLE_HEADER

#include "..\shape\cube.h"

class Apple
{
public:
	explicit Apple(glm::vec3 translateVector)
		: m_cube(new Cube(RED, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f), translateVector, 0.0f, false)), m_isDestroyed(false)
	{
	}
	void Draw(glm::mat4 m_projectionMatrix, unsigned int location)
	{
		if(!m_isDestroyed)
			m_cube->Draw(m_projectionMatrix, location);
	}
	void Destroy(void)
	{
		delete m_cube;
	}
	bool& IsDestroyed(void)
	{
		return m_isDestroyed;
	}
	Shape* CubeObj(void)
	{
		return m_cube;
	}
private:
	Shape* m_cube;
	bool m_isDestroyed;
};

#endif