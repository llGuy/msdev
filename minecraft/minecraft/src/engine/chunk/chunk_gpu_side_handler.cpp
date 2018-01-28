#include "chunk_gpu_side_handler.h"
#include "chunk_data_base.h"

namespace gpu
{
	CGPUHandler::CGPUHandler(void)
		: m_buff()
	{
	}

	void CGPUHandler::Init(BlockYStrip* ys,
		unsigned int index, signed int y, WVec2 chunkCoords, WVec2 negCorner)
	{
		Block* b = &(ys->ystrip[index]);
		glm::vec3 position = b->WPos(chunkCoords, y, negCorner);
		m_blocks.push_back({ position, b->BlockType() });
	}

	void CGPUHandler::CGPUBuffersInit(void)
	{
		::std::size_t components = m_blocks.size();
		BData* p = &(m_blocks[0]);
		m_buff.Init(components, p);
	}
}