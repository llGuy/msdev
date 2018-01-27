#include "engine.h"

Engine::Engine(signed int seed)
	: m_seed(seed), m_chunkMap()
{
	Init();
}

void Engine::Init(void)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			WVec2 c = { i - 2, j - 2 };
			
			Chunk::WCoordChunk wcc = c;
			m_chunkMap[wcc] = Chunk(wcc);
		}
	}
}

WVec2 Engine::CalculateCoordsInChunks(const glm::vec2& worldxz)
{
	signed int x = static_cast<signed int>(worldxz.x);
	signed int z = static_cast<signed int>(worldxz.y);

	return {x / 16, z / 16};
}

glm::vec3 Engine::BlockWPos(glm::vec3 wpos)
{
	WVec2 xz = { static_cast<signed int>(wpos.x), static_cast<signed int>(wpos.z) };
	signed int x8 = (abs(xz.x) + 8) * (xz.x / abs(xz.x));
	signed int z8 = (abs(xz.z) + 8) * (xz.z / abs(xz.z));
	CVec2 coordsInsideChunk = { static_cast<unsigned char>(fabs(x8 % 16)), static_cast<unsigned char>(fabs(z8 % 16)) };
	WVec2 chunkCoords = { x8 / 16, z8 / 16 };
	Chunk::WCoordChunk wcc = { {chunkCoords.x , chunkCoords.z } };
	return m_chunkMap[wcc].BlockWorldCoord(coordsInsideChunk, static_cast<signed int>(wpos.y));
}