#ifndef BLOCK_HEADER
#define BLOCK_HEADER

#include <glm/glm.hpp>

#include "../../texture/texture.h"
#include "../chunk/cvec2.h"

/* the coordinate inside the chunk */
/* is stored in an unsigned char to make it RAM efficient */
struct CCoord
{
	unsigned char cc;
};

class Block
{
public:
	enum class BlType
		: unsigned char
	{
		STONE, DIRT, GRASS, INV /* will add more types of blocks */
	};
	static tex_id m_textureID[3];
	static const unsigned int AVAILABLE_TEXTURES;
public:
	explicit Block(void) = default;
	explicit Block(const CCoord& cc, const BlType& bt);
	explicit Block(const CCoord&& cc, const BlType&& bt);
public:
	/* getter */
	glm::vec3 WPos(const WVec2 chunkCoordinate, signed int y) const;
	CVec2 ExtrCPos(void) const;
	const BlType BlockType(void) const;
private:
	CCoord m_cc;
	BlType m_bt;
};

#endif