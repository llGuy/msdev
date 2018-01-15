#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class Entity;

class Camera
{
public:
	explicit Camera(void)
	{
	}
public:
	void Bind(Entity* ent)
	{

	}
private:
	Entity* m_boundEnt;
};

#endif