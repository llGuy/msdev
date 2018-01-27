#ifndef UNI_LOC_AND_DATA_HEADER
#define UNI_LOC_AND_DATA_HEADER

#include <glm/glm.hpp>

struct UniformLocations
{
	signed int m_uniLocModel;
	signed int m_uniLocProjection;
	signed int m_uniLocView;
	signed int m_uniLocLightPosition;
	signed int m_uniLocEyePosition;
};

#endif