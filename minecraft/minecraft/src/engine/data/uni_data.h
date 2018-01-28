#ifndef UNI_DATA_HEADER
#define UNI_DATA_HEADER

#include <glm/glm.hpp>

namespace minecraft
{
	namespace data
	{
		struct CUData
		{
			glm::mat4 projectionMatrix;
			glm::mat4 viewMatrix;
			glm::vec3 lightPosition;
			glm::vec3 eyePosition;
		};

		struct CUDataLocs
		{
			unsigned int projectionMatrixLocation;
			unsigned int viewMatrixLocation;
			unsigned int lightPositionLocation;
			unsigned int eyePositionLocation;
		};
	}
}

#endif