#ifndef CUNK_HANDLER_HEADER
#define CHUNK_HANDLER_HEADER

#include "../../data/common.h"
#include "../loader/chunk_loader.h"
#include "../../../shader/shprogram.h"
#include "../map/cmap.h"

namespace minecraft
{
	namespace chunk
	{
		class CHandler
		{
		public:
			explicit CHandler(signed int seed);
		public:
			// initializations
			void Init(void);
			void UseSHProgram(void);
			void AfterGLEWInit(void);
			void GetUniform(void);
		public:
			glm::vec3 BlockWPos(glm::vec3 wpos);
			data::CUDataLocs& Locations(void);
			cmap::CMap::iterator Begin(void);
			cmap::CMap::iterator End(void);
		private:
			void ChunkMapInit(void);
			void ChunkLoaderInit(void);
			WVec2 CalculateCoordsInChunks(const glm::vec2& worldxz);
			chunk::Chunk::WCoordChunk CalculateChunkCoordinateOfWPos(const glm::vec3& v) const;
			CVec2 CalculateBlockCoordInChunk(const chunk::Chunk::WCoordChunk& wcc, const glm::vec3& v) const;
			void SHInit(void);
		private:
			::sh::SHProgram m_chunkshprogram;
			data::CUDataLocs m_udataloc;
			loader::CLoader m_chunkloader;
			cmap::CMap m_chunkMap;
			signed int m_seed;
		};
	}
}

#endif