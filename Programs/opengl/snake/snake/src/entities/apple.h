#ifndef APPLE_HEADER
#define APPLE_HEADER

#include "..\shape\cube.h"

class Apple
{
public:
	explicit Apple(glm::vec3 translateVector)
		: m_cube(new Cube(RED, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f), translateVector, 0.0f, false))
	{
	}
	void Draw(glm::mat4 m_projectionMatrix, unsigned int location)
	{
		m_cube->Draw(m_projectionMatrix, location);
	}
private:
	Shape* m_cube;
};

#endif