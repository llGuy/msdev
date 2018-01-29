#include "engine.h"

#include <glm/gtx/transform.hpp>

namespace minecraft
{
	Engine::Engine(signed int seed)
		: m_seed(seed), m_chunkMap(), m_chunkshprogram(), m_camera()
	{
		Init();
	}
	void Engine::Render(void)
	{
		UpdateUniformData();
		for (auto it = m_chunkMap.Begin(); it != m_chunkMap.End(); ++it)
		{
			for (auto& jt : *it)
			{
				chunk::Chunk* c = &jt;
				m_renderer.UniformData(m_udata, m_udataloc);
				m_renderer.AInstancedRender(GL_POINTS, c->Vao(), 0, 1, c->NumBlocks());
			}
		}
	}
	void Engine::Init(void)
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
			{
				WVec2 c = { j - 2, i - 2 };
				chunk::Chunk::WCoordChunk wcc = c;
				m_chunkMap[wcc] = chunk::Chunk(wcc);
			}
		Configure();
	}
	void Engine::TimeDataInit(void)
	{
		m_time.currentTime = std::chrono::high_resolution_clock::now();
		m_time.beginning = std::chrono::high_resolution_clock::now();
	}
	void Engine::Configure(void)
	{
		m_variableConfigs.FOV = glm::radians(60.0f);
		m_variableConfigs.renderDistance = 50.0f;
		m_variableConfigs.mouseSensitivity = 0.02f;
	}
	void Engine::SHProgramInit(void)
	{
		std::vector<const char*> attribs({"vertex_position", "texture_type"});
		m_chunkshprogram.Init("res\\shaders\\block\\vsh.shader", "res\\shaders\\block\\fsh.shader", 
			"res\\shaders\\block\\gsh.shader");
		m_chunkshprogram.Compile();
		m_chunkshprogram.Link(attribs);
	}
	void Engine::UDataInit(unsigned int wwidth, unsigned int wheight)
	{
		m_udataloc.projectionMatrixLocation = glGetUniformLocation(m_chunkshprogram.ProgramID(), "projection_matrix");
		m_udataloc.viewMatrixLocation = glGetUniformLocation(m_chunkshprogram.ProgramID(), "view_matrix");
		m_udataloc.lightPositionLocation = glGetUniformLocation(m_chunkshprogram.ProgramID(), "light_position");
		m_udataloc.eyePositionLocation = glGetUniformLocation(m_chunkshprogram.ProgramID(), "eye_position");

		m_udata.projectionMatrix = glm::perspective(m_variableConfigs.FOV, (float)wwidth / wheight, 0.1f, 50.0f);
	}
	void Engine::AfterGLEWInit(unsigned int wwidth, unsigned int wheight, 
		glm::vec2 cursorPosition)
	{
		m_chunkMap.AfterGLEWInit();
		SHProgramInit();
		UDataInit(wwidth, wheight);
		m_player = new ent::Player();
		m_camera = ent::Camera(cursorPosition);
		m_camera.Bind(m_player);
		TimeDataInit();

		m_chunkshprogram.UseProgram();
	}
	WVec2 Engine::CalculateCoordsInChunks(const glm::vec2& worldxz)
	{
		signed int x = static_cast<signed int>(worldxz.x);
		signed int z = static_cast<signed int>(worldxz.y);
		return { x / 16, z / 16 };
	}
	glm::vec3 Engine::BlockWPos(glm::vec3 wpos)
	{
		chunk::Chunk::WCoordChunk wcc = CalculateChunkCoordinateOfWPos(wpos);
		CVec2 blockChunkCoordinate = CalculateBlockCoordInChunk(wcc, wpos);
		return m_chunkMap[wcc].BlockWorldCoord(blockChunkCoordinate, static_cast<signed int>(wpos.y));
	}
	void Engine::RecieveKeyInput(key_t&& key)
	{
		switch (key)
		{
		case key_t::W:
			m_player->Move(ent::Entity::move_t::FORWARD, &m_time);
			break;
		case key_t::A:
			m_player->Strafe(ent::Entity::strafe_t::LEFT, &m_time);
			break;
		case key_t::S:
			m_player->Move(ent::Entity::move_t::BACKWARD, &m_time);
			break;
		case key_t::D:
			m_player->Strafe(ent::Entity::strafe_t::RIGHT, &m_time);
			break;
		case key_t::SPACE:
			m_player->VMove(ent::Entity::vmove_t::UP, &m_time);
			break;
		case key_t::LSHIFT:
			m_player->VMove(ent::Entity::vmove_t::DOWN, &m_time);
			break;
		}
	}
	void Engine::RecieveMouseMovement(glm::vec2 newMousePosition)
	{
		m_camera.Look(newMousePosition, m_variableConfigs.mouseSensitivity);
	}
	chunk::Chunk::WCoordChunk Engine::CalculateChunkCoordinateOfWPos(const glm::vec3& v) const
	{
		WVec2 xz = { static_cast<signed int>(v.x), static_cast<signed int>(v.z) };
		signed int x = xz.x == 0 ? 0 : (abs(xz.x) + 8) * (xz.x / abs(xz.x)) / 16;
		signed int z = xz.z == 0 ? 0 : (abs(xz.z) + 8) * (xz.z / abs(xz.z)) / 16;
		return { {x, z } };
	}
	CVec2 Engine::CalculateBlockCoordInChunk(const chunk::Chunk::WCoordChunk& wcc, const glm::vec3& v) const
	{
		unsigned char x = wcc.wpos.x == 0 ? static_cast<unsigned char>(v.x + 8) :
			static_cast<unsigned char>(v.x - (wcc.wpos.x * 16 + 8 * (-wcc.wpos.x / wcc.wpos.x)));
		unsigned char z = wcc.wpos.z == 0 ? static_cast<unsigned char>(v.z + 8) :
			static_cast<unsigned char>(v.z - (wcc.wpos.z * 16 + 8 * (-wcc.wpos.z / wcc.wpos.z)));
		return { x , z };
	}
	void Engine::UpdateUniformData(void)
	{
		m_udata.viewMatrix = m_camera.ViewMatrix();

		m_time.deltaT = (double)((std::chrono::high_resolution_clock::now() - m_time.currentTime).count()) / 1000000000;
		m_time.currentTime = std::chrono::high_resolution_clock::now();
	}
}