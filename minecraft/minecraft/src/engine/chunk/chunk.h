#ifndef CHUNK_HEADER
#define CHUNK_HEADER

#include "../block/block.h"
#include "chunk_data_base.h"

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
	Chunk(void) : m_wcoordChunk() {}
	explicit Chunk(const WCoordChunk& wcoordChunk);
	explicit Chunk(const WCoordChunk&& wcoordChunk);
public:
	/* getters */
	glm::vec3 BlockWorldCoord(const CVec2 cc, signed int elevation);
	WCoordChunk ChunkCoordinate(void);
	Block::BlType BlockType(const CVec2 cc, signed int elevation);
private:
	void Init(void);
	WVec2 NegativeCornerWPos(void) const;
private:
	WCoordChunk m_wcoordChunk;
	ChunkDB m_dataBase;
};

#endif