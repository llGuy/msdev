#include "engine.h"

namespace minecraft
{
	Engine::Engine(signed int seed)
		: m_seed(seed), m_chunkMap()
	{
		Init();
	}

	void Engine::Init(void)
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
			{
				WVec2 c = { j - 2, i - 2 };
				Chunk::WCoordChunk wcc = c;
				m_chunkMap[wcc] = Chunk(wcc);
			}
	}

	void Engine::AfterGLEWInit(void)
	{
		m_chunkMap.AfterGLEWInit();
	}

	WVec2 Engine::CalculateCoordsInChunks(const glm::vec2& worldxz)
	{
		signed int x = static_cast<signed int>(worldxz.x);
		signed int z = static_cast<signed int>(worldxz.y);
		return { x / 16, z / 16 };
	}

	glm::vec3 Engine::BlockWPos(glm::vec3 wpos)
	{
		Chunk::WCoordChunk wcc = CalculateChunkCoordinateOfWPos(wpos);
		CVec2 blockChunkCoordinate = CalculateBlockCoordInChunk(wcc, wpos);
		return m_chunkMap[wcc].BlockWorldCoord(blockChunkCoordinate, static_cast<signed int>(wpos.y));
	}

	Chunk::WCoordChunk Engine::CalculateChunkCoordinateOfWPos(const glm::vec3& v) const
	{
		WVec2 xz = { static_cast<signed int>(v.x), static_cast<signed int>(v.z) };
		signed int x = xz.x == 0 ? 0 : (abs(xz.x) + 8) * (xz.x / abs(xz.x)) / 16;
		signed int z = xz.z == 0 ? 0 : (abs(xz.z) + 8) * (xz.z / abs(xz.z)) / 16;
		return { {x, z } };
	}

	CVec2 Engine::CalculateBlockCoordInChunk(const Chunk::WCoordChunk& wcc, const glm::vec3& v) const
	{
		unsigned char x = wcc.wpos.x == 0 ? static_cast<unsigned char>(v.x + 8) :
			static_cast<unsigned char>(v.x - (wcc.wpos.x * 16 + 8 * (-wcc.wpos.x / wcc.wpos.x)));
		unsigned char z = wcc.wpos.z == 0 ? static_cast<unsigned char>(v.z + 8) :
			static_cast<unsigned char>(v.z - (wcc.wpos.z * 16 + 8 * (-wcc.wpos.z / wcc.wpos.z)));
		return { x , z };
	}
}