#ifndef CHUNK_HEADER
#define CHUNK_HEADER

#include "../block/block.h"
#include "database/chunk_data_base.h"
#include "biome/plains/plains.h"
#include "noise/regular/reg_perlin_noise.h"
#include "gpu/gpuhandler/chunk_gpu_side_handler.h"

namespace minecraft
{
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
			explicit Chunk(void);
			explicit Chunk(signed int seed) : m_wcoordChunk(), m_biome(new Biome), m_dataBase(seed, m_biome->MaxHeight()) {}
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
			void Load(void);
			WVec2 NegativeCornerWPos(void) const;
		private:
			WCoordChunk m_wcoordChunk;
			Biome* m_biome;
			ChunkDB m_dataBase;
		};
	}
}

#endif