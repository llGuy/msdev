#include "chunk.h"

Chunk::Chunk(const WCoordChunk& wcoordChunk)
	: m_wcoordChunk(wcoordChunk)
{
	Init();
}

Chunk::Chunk(const WCoordChunk&& wcoordChunk)
	: m_wcoordChunk(wcoordChunk)
{
	Init();
}

void Chunk::Init(void)
{
	m_dataBase.Initialize();
}

glm::vec3 Chunk::BlockWorldCoord(const CVec2 cc, signed int elevation) 
{
	return m_dataBase.WCoord(m_wcoordChunk.wpos, cc, elevation, NegativeCornerWPos());
}

Block::BlType Chunk::BlockType(const CVec2 cc, signed int elevation) 
{
	return m_dataBase.BlockType(cc, elevation);
}

Chunk::WCoordChunk Chunk::ChunkCoordinate(void)
{
	return m_wcoordChunk;
}

WVec2 Chunk::NegativeCornerWPos(void) const
{
	/*signed int xcomp = (abs(m_wcoordChunk.wpos.x * 16) - 8.0f) * abs(m_wcoordChunk.wpos.x) / (m_wcoordChunk.wpos.x);
	signed int zcomp = (abs(m_wcoordChunk.wpos.z * 16) - 8.0f) * abs(m_wcoordChunk.wpos.z) / (m_wcoordChunk.wpos.z);

	signed int finalVx = (m_wcoordChunk.wpos.x == 0 ? -8 : xcomp);
	signed int finalVz = (m_wcoordChunk.wpos.z == 0 ? -8 : zcomp);*/
	return { m_wcoordChunk.wpos.x * 16 - 8, m_wcoordChunk.wpos.z * 16 - 8 };
}