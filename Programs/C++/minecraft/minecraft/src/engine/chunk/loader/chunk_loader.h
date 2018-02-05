#ifndef CHUNK_LOADER_HEADER
#define CHUNK_LOADER_HEADER

#include "../map/cmap.h"
#include "../../entities/player/player.h"

#include <thread>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>

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
				explicit CLoader(cmap::CMap* cm, ent::Entity* player, signed int seed);
			public:
				void UpdateChunks(std::function<bool(int, int)> x, std::function<void(int&)> xi,
					std::function<bool(int, int)> z, std::function<void(int&)> zi,
					int startx, int startz);
				// spawn thread
				void Spawn(GLFWwindow* window);
				chunk::Chunk::WCoordChunk PlayerWPosInChunkCoordinates(void);
			private:
				std::thread m_clthread[2];
				cmap::CMap* m_currentMap;
				ent::Entity* m_player;
				Chunk::WCoordChunk m_playerCurrentChunkCoordinates;
				signed int m_seed;
			};
		}
	}
}

#endif