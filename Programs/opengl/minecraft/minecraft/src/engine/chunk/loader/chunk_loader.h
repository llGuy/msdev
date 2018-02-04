#ifndef CHUNK_LOADER_HEADER
#define CHUNK_LOADER_HEADER

#include "../map/cmap.h"

#include <thread>
#include <iostream>

namespace minecraft
{
	namespace chunk
	{
		namespace loader
		{
			class CLoader
			{
			public:
				explicit CLoader(void) = default;
				explicit CLoader(cmap::CMap* cm);
			public:
				void UpdateChunks(void);
				// spawn thread
				void Spawn(void);
			private:
				std::thread m_clthread;
				cmap::CMap* m_currentMap;
			};
		}
	}
}

#endif