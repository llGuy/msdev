#ifndef CHUNK_GPU_SIDE_HANDLER_HEADER
#define CHUNK_GPU_SIDE_HANDLER_HEADER

#include "blockystrip.h"
#include "cgpubuffer.h"
#include "gpublockdata.h"

namespace gpu
{
	/* chunk GPU side handler will create the buffer with the VAOs */
	class CGPUHandler
	{
	public:
		
		explicit CGPUHandler(void);
	public:
		/* initializations are gradual							*/
		/* (done in the for loop in the ChunkDB)				*/
		void Init(BlockYStrip* ys, unsigned int index, signed int y,
			WVec2 chunkCoords, WVec2 negCorner);
	public:
		/* gets called in Init to initialize the texture maps	*/
		/* for the buffers to map   the blocks properly			*/
		/* in order to instance the block drawing				*/
		void CGPUBuffersInit(void);
	private:
		CGPUBuffer m_buff;
		std::vector<BData> m_blocks;
	};
}

#endif