#ifndef ENGINE_HEADER
#define ENGINE_HEADER

#include <unordered_map>
#include <vector>

#include "../shader/shprogram.h"
#include "chunk/chunk.h"
#include "renderer/renderer.h"
#include "chunk/map/cmap.h"
#include "../shader/shprogram.h"
#include "configs/configs.h"
#include "entities/player/player.h"
#include "entities/camera/camera.h"
#include "../texture/texture.h"

namespace minecraft
{
	/* Minecraft engine which will render everything */
	class Engine
	{
	public:
		enum class key_t
		{
			W,				// forward
			
			A,				// left
			
			S,				// backward
			
			D,				// right
			
			SPACE,			// jump
			
			LSHIFT			// crouch
		};
		explicit Engine(void);
		void AfterGLEWInit(unsigned int wwidth, unsigned int wheight, 
			glm::vec2 cursorPos);
	public:
		/* getters */
		glm::vec3 BlockWPos(glm::vec3 wpos);
		void RecieveKeyInput(key_t&& key);
		void RecieveMouseMovement(glm::vec2 newMousePosition);
		void Render(void);
	private:
		void Init(void);
		void TimeDataInit(void);
		void Configure(void);
		void SHProgramInit(void);
		void UDataInit(unsigned int wwidth, unsigned int wheight);
		WVec2 CalculateCoordsInChunks(const glm::vec2& worldxz);
		chunk::Chunk::WCoordChunk CalculateChunkCoordinateOfWPos(const glm::vec3& v) const;
		CVec2 CalculateBlockCoordInChunk(const chunk::Chunk::WCoordChunk& wcc, const glm::vec3& v) const;
		void UpdateUniformData(void);
	private:
		Texture m_textureAtlas;
		ent::Camera m_camera;
		ent::Entity* m_player;
		data::Time m_time;
		data::CUData m_udata;
		data::CUDataLocs m_udataloc;
		rnd::Renderer m_renderer;
		configs::VConfigs m_variableConfigs;
		configs::CConfigs m_constantConfigs;
		chunk::cmap::CMap m_chunkMap;
		::sh::SHProgram m_chunkshprogram;
		signed int m_seed;
		float m_fps;
	};
}

#endif
