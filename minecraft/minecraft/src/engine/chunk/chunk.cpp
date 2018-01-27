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
	return m_dataBase.WCoord(m_wcoordChunk.wpos, cc, elevation);
}

Block::BlType Chunk::BlockType(const CVec2 cc, signed int elevation) 
{
	return m_dataBase.BlockType(cc, elevation);
}

Chunk::WCoordChunk Chunk::ChunkCoordinate(void)
{
	return m_wcoordChunk;
}