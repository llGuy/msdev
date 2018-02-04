#include "chunk_loader.h"

namespace minecraft
{
	namespace chunk
	{
		namespace loader
		{
			void CLoader::UpdateChunks(void)
			{
				for (;;)
					std::cout << "thread is working!" << std::endl;
			}
			CLoader::CLoader(cmap::CMap* cm)
			{
				m_currentMap = cm;
			}
			// spawn thread
			void CLoader::Spawn(void)
			{
				m_clthread = std::thread(&CLoader::UpdateChunks, this);
				m_clthread.detach();
			}
		}
	}
}