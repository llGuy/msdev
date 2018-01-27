#ifndef UNI_DATA_HEADER
#define UNI_DATA_HEADER

#include <glm/glm.hpp>

struct UData
{
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 modelMatrix;
	glm::vec3 lightPosition;
	glm::vec3 eyePosition;
	float deltat;
};

#endif