#include "block.h"

const unsigned int Block::AVAILABLE_TEXTURES = 
	static_cast<unsigned int>(Block::BlType::INV) - 1;

tex_id Block::m_textureID[3] { 0 };

Block::Block(const CCoord& cc, const BlType& bt)
	: m_cc(cc), m_bt(bt)
{
}

Block::Block(const CCoord&& cc, const BlType&& bt)
	: m_cc(cc), m_bt(bt)
{
}

glm::vec3 Block::WPos(const WVec2 chunkCoordinate, signed int y, const WVec2 negativeCornerWPos) const
{
	CVec2 blockPosOnChunk = ExtrCPos();
	return glm::vec3(negativeCornerWPos.x + blockPosOnChunk.x, y,
		negativeCornerWPos.z + blockPosOnChunk.z);
} 

CVec2 Block::ExtrCPos(void) const
{
	return { static_cast<unsigned char>(m_cc.cc >> 4), static_cast<unsigned char>(m_cc.cc & 0x0f) };
}

const Block::BlType Block::BlockType(void) const
{
	return m_bt;
}