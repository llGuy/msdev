#include "chunk.h"

namespace chunk
{
	Chunk::Chunk(const WCoordChunk& wcoordChunk, signed int seed)
		: m_wcoordChunk(wcoordChunk), m_biome(new Plains), m_dataBase(seed, m_biome->MaxHeight())
	{
		Load();
	}

	Chunk::Chunk(const WCoordChunk&& wcoordChunk, signed int seed)
		: m_wcoordChunk(wcoordChunk), m_biome(new Plains), m_dataBase(seed, m_biome->MaxHeight())
	{
		Load();
	}

	void Chunk::Load(void)
	{
		m_dataBase.Load(m_wcoordChunk.wpos, NegativeCornerWPos(), m_biome);
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

	::std::size_t Chunk::NumBlocks(void)
	{
		return m_dataBase.NumBlocks();
	}

	VAO* Chunk::Vao(void)
	{
		return m_dataBase.Vao();
	}
}