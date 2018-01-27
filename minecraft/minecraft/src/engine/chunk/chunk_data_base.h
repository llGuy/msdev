#ifndef CHUNK_DATA_BASE_HEADER
#define CHUNK_DATA_BASE_HEADER

#include <unordered_map>

#include "../block/block.h"
#include "cvec2.h"

class ChunkDB
{
public:
	explicit ChunkDB(void) = default;
public:
	void Initialize(void)
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
					m_blocks[Index(cc)].ystrip[y - 25] = 
						Block(CompressChunkCoord(cc), Block::BlType::DIRT);
				}
			}
		}
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
private:
	unsigned char Index(CVec2 ccoord) const
	{
		return ccoord.x + ccoord.z * 16;
	}
	CCoord CompressChunkCoord(CVec2 cc) const
	{
		unsigned char x = static_cast<unsigned char>(cc.x);
		unsigned char z = static_cast<unsigned char>(cc.z);
		return { static_cast<unsigned char>((x << 4) + z) };
	}
private:
	typedef std::unordered_map<unsigned char, Block> ysmap_t;
	struct BlockYStrip
	{
		ysmap_t ystrip;
	};
	BlockYStrip m_blocks[16 * 16];
};

#endif