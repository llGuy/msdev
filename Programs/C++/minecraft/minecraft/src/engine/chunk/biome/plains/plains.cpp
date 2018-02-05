#include "plains.h"

Plains::Plains(void)
	: MHEIGHT(20), DIRTHEIGHTMIN(0.8f), STONEHEIGHTMIN(0.1f),
	BEDROCKHEIGHTMIN(0.0f)
{
}

const signed int Plains::MaxHeight(void)
{
	return MHEIGHT;
}

Block::BlType Plains::BlockType(signed int y, signed int bysmheight, signed int bottom)
{
	if (y - bottom == bysmheight - 1) 
		return Block::BlType::GRASS;
	else if (y - bottom >= DIRTHEIGHTMIN * bysmheight)
		return Block::BlType::DIRT;
	else if (y - bottom >= STONEHEIGHTMIN * bysmheight)
		return Block::BlType::STONE;
	else 
		return Block::BlType::BEDROCK;
}