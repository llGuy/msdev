#ifndef CHUNK_DATA_BASE_HEADER
#define CHUNK_DATA_BASE_HEADER

#include <unordered_map>

#include "../block/block.h"
#include "chunk_gpu_side_handler.h"
#include "cvec2.h"
#include "blockystrip.h"

namespace chunk
{
	class ChunkDB
	{
	public:
		explicit ChunkDB(void) = default;
	public:
		void Init(WVec2 chunkCoords, WVec2 negCorner)
		{
			for (unsigned int z = 0; z < 16; ++z)
			{
				for (unsigned int x = 0; x < 16; ++x)
				{
					for (unsigned int y = 0; y < 50; ++y)
					{
						CVec2 cc = { static_cast<unsigned char>(x), static_cast<unsigned char>(z) };
						/* TEMPORARY THAT THE BLOCK TYPE IS DIRT */
						/* THIS WILL CHANGE LATER */
						BlockYStrip& bys = m_blocks[Index(cc)];
						bys.ystrip[y - 25] = Block(CompressChunkCoord(cc), Block::BlType::DIRT);
						m_gpuh.Init(&bys, Index(cc), y - 25, chunkCoords, negCorner);
					}
				}
			}
		}
		void AfterGLEWInit(void)
		{
			m_gpuh.CGPUBuffersInit();
		}
	public:
		/* getter */
		glm::vec3 WCoord(WVec2 wchunkCoord, CVec2 ccoord, unsigned char elevation, const WVec2&& negativeCornerWPos)
		{
			return m_blocks[Index(ccoord)].ystrip[elevation].WPos(wchunkCoord, elevation, negativeCornerWPos);
		}
		const Block::BlType BlockType(CVec2 ccoord, unsigned char elevation)
		{
			return m_blocks[Index(ccoord)].ystrip[elevation].BlockType();
		}
		unsigned char Index(CVec2 ccoord) const
		{
			return ccoord.x + ccoord.z * 16;
		}
		::std::size_t NumBlocks(void)
		{
			return m_gpuh.NumBlocks();
		}
		VAO* Vao(void)
		{
			return m_gpuh.Vao();
		}
	private:
		CCoord CompressChunkCoord(CVec2 cc) const
		{
			unsigned char x = static_cast<unsigned char>(cc.x);
			unsigned char z = static_cast<unsigned char>(cc.z);
			return { static_cast<unsigned char>((x << 4) + z) };
		}
	private:
		gpu::CGPUHandler m_gpuh;
		BlockYStrip m_blocks[16 * 16];
	};
}

#endif