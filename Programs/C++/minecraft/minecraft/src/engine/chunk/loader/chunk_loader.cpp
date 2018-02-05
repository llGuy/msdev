#include "chunk_loader.h"
#include "../../../log.h"

namespace minecraft
{
	namespace chunk
	{
		namespace loader
		{
			void CLoader::UpdateChunks(std::function<bool(int, int)> xf, std::function<void(int&)> xi,
				std::function<bool(int, int)> zf, std::function<void(int&)> zi,
				int startx, int startz)
			{
				for (;;)
				{
					Chunk::WCoordChunk wc = PlayerWPosInChunkCoordinates();
					if (wc != m_playerCurrentChunkCoordinates)
					{
						for (int z = wc.wpos.z + startz; zf(z, wc.wpos.z - startz); zi(z))
						{
							for (signed int x = wc.wpos.x + startx; xf(x, wc.wpos.x - startx); xi(x))
							{
								WVec2 c = { x, z };
								chunk::Chunk::WCoordChunk wcc = c;
								for (; m_currentMap->UpdateState() == cmap::CMap::update_t::UPDATE_ACTIVE; )
								{
								}
								chunk::Chunk& ch = m_currentMap->operator[](wcc);
								if (!(ch.Loaded()) && !ch.BufferLoaded())
								{
									m_currentMap->operator[](wcc) = Chunk(wcc, m_seed);
									Log("generated new chunk");
								}
							}
						}
					}
				}
			}
			CLoader::CLoader(cmap::CMap* cm, ent::Entity* player, signed int seed)
				: m_currentMap(cm), m_player(player)
			{
			}
			// spawn thread
			void CLoader::Spawn(GLFWwindow* window)
			{
				m_playerCurrentChunkCoordinates = { { -0x551, -0x914} };
				m_clthread[0] = std::thread(&CLoader::UpdateChunks, this,
					[=](int a, int b) {return a < b; } /* conditional lambda */, [&](int& x) { ++x; },/* incremental lambda */
					[=](int a, int b) {return a < b; } /* conditional lambda */, [&](int& z) { ++z; },/* incremental lambda */ -4, -4);
				m_clthread[1] = std::thread(&CLoader::UpdateChunks, this,
					[=](int a, int b) {return a >= b; }, [&](int& x) { --x; },
					[=](int a, int b) {return a < b; }, [&](int& z) { ++z; }, 4, -4);

				m_clthread[0].detach();
				m_clthread[1].detach();
			}
			chunk::Chunk::WCoordChunk CLoader::PlayerWPosInChunkCoordinates(void)
			{
				glm::vec3 v = *m_player->EntityWorldPosition();
				WVec2 xz = { static_cast<signed int>(v.x), static_cast<signed int>(v.z) };
				signed int x = xz.x == 0 ? 0 : (abs(xz.x) + 8) * (xz.x / abs(xz.x)) / 16;
				signed int z = xz.z == 0 ? 0 : (abs(xz.z) + 8) * (xz.z / abs(xz.z)) / 16;
				return { { x, z } };
			}
		}
	}
}