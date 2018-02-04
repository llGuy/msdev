#ifndef PLAINS_BIOME_HEADER
#define PLAINS_BIOME_HEADER

#include "../biome.h"

class Plains
	: public Biome
{
public:
	explicit Plains(void);
public:
	virtual const signed int MaxHeight(void) override;
	Block::BlType BlockType(signed int y, signed int maxHeight, signed int bottom) override;
private:
	const signed int MHEIGHT;
	const float DIRTHEIGHTMIN;
	const float STONEHEIGHTMIN;
	const float BEDROCKHEIGHTMIN;
};

#endif