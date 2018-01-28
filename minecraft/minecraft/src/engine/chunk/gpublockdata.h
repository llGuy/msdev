#ifndef GPUBLOCKDATA_HEADER
#define GPUBLOCKDATA_HEADER

#include "../block/block.h"
#include <glm/glm.hpp>

namespace gpu
{
	struct BData
	{
		glm::vec3 pos;
		Block::BlType tex;
	};
}

#endif