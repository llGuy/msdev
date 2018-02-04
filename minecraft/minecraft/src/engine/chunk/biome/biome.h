#ifndef BIOME_HEADER
#define BIOME_HEADER

#include "../../block/block.h"

class Biome
{
public:
	virtual const signed int MaxHeight(void) { return 0; }
	virtual Block::BlType BlockType(signed int y, signed int maxHeight, signed int bottom) { return Block::BlType::INV; }
};

#endif