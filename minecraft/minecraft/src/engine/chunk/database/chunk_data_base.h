#ifndef CHUNK_DATA_BASE_HEADER
#define CHUNK_DATA_BASE_HEADER

#include <unordered_map>

#include "../../block/block.h"
#include "../gpu/gpuhandler/chunk_gpu_side_handler.h"
#include "../cdata/cvec2.h"
#include "../noise/regular/reg_perlin_noise.h"
#include "blockystrip.h"
#include "../biome/plains/plains.h"
#include "../../utility/glm_vecio.h"

namespace chunk
{
	class ChunkDB
	{
	public:
		explicit ChunkDB(signed int seed, const signed int mh)
			: m_perlinNoiseGenerator(new noise::Reg_PerlinNoise(seed, mh))
		{
		}
	public:
		void Load(WVec2 chunkCoords, WVec2 negCorner, Biome* biome)
		{
			GenerateCorners(negCorner);
			m_gradientVectors = m_perlinNoiseGenerator->GVectors(m_corners);
			for (signed int z = 0; z < 16; ++z)
			{
				for (signed int x = 0; x < 16; ++x)
				{
					float height = Height(negCorner, x, z);
					for (signed int y = -30; y < static_cast<signed int>(height); ++y)
					{
						CVec2 cc = { static_cast<unsigned char>(x), static_cast<unsigned char>(z) };
						BlockYStrip& bys = m_blocks[Index(cc)];
						bys.ystrip[y] = Block(CompressChunkCoord(cc), biome->BlockType(y, static_cast<signed int>(height) + 30, -30));
					}
				}
			}
			LoadGPUData(chunkCoords, negCorner);
		}
		void AfterGLEWInit(void)
		{
			m_gpuh.LoadGPUBuffer();
		}
	public:
		/* getter */
		glm::vec3 WCoord(WVec2 wchunkCoord, CVec2 ccoord, unsigned char elevation, const WVec2&& negativeCornerWPos)
		{
			return m_blocks[Index(ccoord)].ystrip[elevation].WPos(wchunkCoord, elevation, negativeCornerWPos);
		}
		const Block::BlType BlockType(CVec2 ccoord, unsigned char elevation)
		{
			return m_blocks[Index(ccoord)].ystrip[elevation].BlockType();
		}
		unsigned char Index(CVec2 ccoord) const
		{
			return ccoord.x + ccoord.z * 16;
		}
		::std::size_t NumBlocks(void)
		{
			return m_gpuh.NumBlocks();
		}
		VAO* Vao(void)
		{
			return m_gpuh.Vao();
		}
	private:
		void LoadGPUData(WVec2 chunkCoords, WVec2 negCorner)
		{
			for (signed int z = 0; z < 16; ++z)
			{
				for (signed int x = 0; x < 16; ++x)
				{
					CVec2 cc = { static_cast<unsigned char>(x), static_cast<unsigned char>(z) };
					BlockYStrip& bys = m_blocks[Index(cc)];
					for (auto& i : bys.ystrip)
					{
						if(BlockIsVisible(x, i.first, z, bys)) m_gpuh.Load(&bys, Index(cc), i.first, chunkCoords, negCorner);
					}
				}
			}
		}
		bool BlockIsVisible(signed int x, signed int y, signed int z, const BlockYStrip& bys)
		{
			// is at the edge of the chunk
			if (x == 15 || z == 15 || x == 0 || z == 0) return true;
			// check x axis
			CVec2 cc = { static_cast<unsigned char>(x + 1), static_cast<unsigned char>(z) };
			if (m_blocks[Index(cc)].ystrip.find(y) == m_blocks[Index(cc)].ystrip.end()) return true;
			cc = { static_cast<unsigned char>(x - 1), static_cast<unsigned char>(z) };
			if (m_blocks[Index(cc)].ystrip.find(y) == m_blocks[Index(cc)].ystrip.end()) return true;

			cc = { static_cast<unsigned char>(x), static_cast<unsigned char>(z + 1) };
			if (m_blocks[Index(cc)].ystrip.find(y) == m_blocks[Index(cc)].ystrip.end()) return true;
			cc = { static_cast<unsigned char>(x), static_cast<unsigned char>(z - 1) };
			if (m_blocks[Index(cc)].ystrip.find(y) == m_blocks[Index(cc)].ystrip.end()) return true;

			// check y axis
			cc = { static_cast<unsigned char>(x), static_cast<unsigned char>(z) };
			if (m_blocks[Index(cc)].ystrip.find(y + 1) == m_blocks[Index(cc)].ystrip.end()) return true;
			if (m_blocks[Index(cc)].ystrip.find(y - 1) == m_blocks[Index(cc)].ystrip.end()) return true;

			else return false;
		}
		CCoord CompressChunkCoord(CVec2 cc) const
		{
			unsigned char x = static_cast<unsigned char>(cc.x);
			unsigned char z = static_cast<unsigned char>(cc.z);
			return { static_cast<unsigned char>((x << 4) + z) };
		}
		void GenerateCorners(WVec2 negCorner)
		{
			glm::vec2 negativeCorner = glm::vec2(static_cast<float>(negCorner.x), static_cast<float>(negCorner.z));

			/* using the negative corner of the chunk */
			/* the program calculates the positions of the corners of the chunk */
			m_corners.nn = glm::vec2(negativeCorner.x - 0.5f,
				negativeCorner.y - 0.5f);
			m_corners.np = glm::vec2(negativeCorner.x - 0.5f,
				negativeCorner.y + 15.5f);
			m_corners.pn = glm::vec2(negativeCorner.x + 15.5f,
				negativeCorner.y - 0.5f);
			m_corners.pp = glm::vec2(negativeCorner.x + 15.5f,
				negativeCorner.y + 15.5f);
		}
		float Height(const WVec2& negCorner, const signed int& x, const signed int& z)
		{
			float blockx = static_cast<float>(negCorner.x + x);
			float blockz = static_cast<float>(negCorner.z + z);
			glm::vec2 blockxzworld = glm::vec2(blockx, blockz);
			return m_perlinNoiseGenerator->Height(blockxzworld, m_corners, m_gradientVectors);
		}
	private:
		CCorners m_corners;
		gpu::CGPUHandler m_gpuh;
		noise::PerlinNoise::GradientVectors m_gradientVectors;
		noise::PerlinNoise* m_perlinNoiseGenerator;
		BlockYStrip m_blocks[16 * 16];
	};
}

#endif