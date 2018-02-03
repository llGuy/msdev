#ifndef CHUNK_HEADER
#define CHUNK_HEADER

#include "../block/block.h"
#include "chunk_data_base.h"
#include "noise/regular/reg_perlin_noise.h"
#include "chunk_gpu_side_handler.h"

namespace chunk
{
	class Chunk
	{
	public:
		struct WCoordChunk
		{
			WCoordChunk(void) = default;
			WCoordChunk(const WVec2& v)
				: wpos(v) {}
			WVec2 wpos;
			bool operator==(const WCoordChunk& c)
			{
				return (c.wpos.x == wpos.x && c.wpos.z == wpos.z);
			}
		};
		Chunk(signed int seed) : m_wcoordChunk(), m_dataBase(seed) {}
		explicit Chunk(const WCoordChunk& wcoordChunk, signed int seed);
		explicit Chunk(const WCoordChunk&& wcoordChunk, signed int seed);
		void AfterGLEWInit(void);
	public:
		/* getters */
		glm::vec3 BlockWorldCoord(const CVec2 cc, signed int elevation);
		WCoordChunk ChunkCoordinate(void);
		Block::BlType BlockType(const CVec2 cc, signed int elevation);
		::std::size_t NumBlocks(void);
		VAO* Vao(void);
	private:
		void Init(void);
		WVec2 NegativeCornerWPos(void) const;
	private:
		WCoordChunk m_wcoordChunk;
		ChunkDB m_dataBase;
	};
}

#endif