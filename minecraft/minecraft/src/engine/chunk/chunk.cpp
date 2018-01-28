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
	m_dataBase.Init(m_wcoordChunk.wpos, NegativeCornerWPos());
}

void Chunk::AfterGLEWInit(void) 
{
	m_dataBase.AfterGLEWInit();
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
	return { m_wcoordChunk.wpos.x * 16 - 8, m_wcoordChunk.wpos.z * 16 - 8 };
}