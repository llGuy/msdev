#ifndef ENGINE_HEADER
#define ENGINE_HEADER

#include <unordered_map>
#include <vector>

#include "../shader/shprogram.h"
#include "chunk/chunk.h"
#include "chunk/map/cmap.h"

/* Minecraft engine which will render everything */
class Engine
{
public:
	explicit Engine(signed int seed);
public:
	 /* getters */
	glm::vec3 BlockWPos(glm::vec3 wpos);
private:
	void Init(void);
	WVec2 CalculateCoordsInChunks(const glm::vec2& worldxz);
	Chunk::WCoordChunk CalculateChunkCoordinateOfWPos(const glm::vec3& v) const;
	CVec2 CalculateBlockCoordInChunk(const Chunk::WCoordChunk& wcc, const glm::vec3& v) const;
private:
	cmap::CMap m_chunkMap;
	signed int m_seed;
};

#endif
