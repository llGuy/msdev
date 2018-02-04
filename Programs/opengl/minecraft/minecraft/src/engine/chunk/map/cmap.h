#ifndef CMAP_HEADER
#define CMAP_HEADER

#include <list>
#include <unordered_map>
#include <vector>

#include "../chunk.h"
#include "../loader/chunk_loader.h"

namespace minecraft
{
	namespace chunk
	{
		namespace cmap
		{
			struct CHash
			{
				int operator()(const Chunk::WCoordChunk& v) const
				{
					return std::hash<int>()(v.wpos.x)
						^ (std::hash<int>()(v.wpos.z) >> 1) << 1;
				}
			};

			class CMap
			{
			public:
				typedef std::vector<std::list<Chunk>>::iterator iterator;

				CMap(signed int seed)
					: m_nll(4), m_size(0), m_seed(seed)
				{
					for (unsigned int i = 0; i < m_nll; ++i)
						m_llists.push_back(std::list<Chunk>());
				}
				void Load(Chunk::WCoordChunk& v)
				{
					int h = CHash()(v) % m_nll;
					for (auto& i : m_llists[h])
						if (i.ChunkCoordinate() == v) return;
					App(v);
				}
				Chunk& operator[](Chunk::WCoordChunk& v)
				{
					int h = CHash()(v) % m_nll;
					for (auto& i : m_llists[h])
						if (i.ChunkCoordinate() == v) return i;
					return App(v);
				}
				void AfterGLEWInit(void)
				{
					for (auto& i : m_llists)
						for (auto& j : i)
						{
							j.AfterGLEWInit();
						}
				}
				iterator Begin(void)
				{
					return m_llists.begin();
				}
				iterator End(void)
				{
					return m_llists.end();
				}
				::std::size_t Size(void) const
				{
					return m_size;
				}
			private:
				/* append */
				Chunk & App(const Chunk::WCoordChunk& v)
				{
					if (m_size == m_nll)
					{
						for (std::size_t i = 0; i < m_nll; ++i)
							m_llists.push_back(std::list<Chunk>());
						m_nll *= 2;
					}
					int h = CHash()(v) % m_nll;
					m_llists[h].push_back(Chunk(m_seed));
					Chunk& newChunk = m_llists[h].back();
					++m_size;
					return newChunk;
				}
			private:
				std::vector<std::list<Chunk>> m_llists;
				/* number of linked lists */
				std::size_t m_nll;
				/* size of the Chunk Map */
				std::size_t m_size;
				signed int m_seed;
			};
		}
	}
}

#endif