#ifndef WATER_HEADER
#define WATER_HEADER

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../data/vertex_data.h"
#include "../data/index_data.h"
#include "../data/uni_loc_and_data.h"
#include "../buffer/buffer.h"
#include "waterFBO.h"

class Water
{
public:
	struct Locs
	{
		signed int proj;
		signed int view;
		signed int model;
	};
	explicit Water(const glm::vec3&& translateVector, const float&& radius)
		: m_translateMatrix(glm::translate(translateVector)), m_radius(radius),
		m_shp("res\\water\\vsh.shader", "res\\water\\fsh.shader", "", false),
		m_wfb()
	{
		CreateVertices();
		CreateIndices();
		InitBuffer();
		ShadersInit();
		GetUniformLocations();
	}
	void Draw(glm::mat4& projection, glm::mat4& view)
	{
		m_shp.UseProgram();
		m_buffer.BindAll();
		SendUniformData(projection, view);
		glDrawElements(GL_TRIANGLES, m_id.numIndices, GL_UNSIGNED_SHORT, 0);
	}
private:
	void CreateVertices(void)
	{
		Vertex vertices[]
		{
			{glm::vec3(m_radius, 0.0f, m_radius), glm::vec3(0.0f, 0.0f, 1.0f)},
			{glm::vec3(-m_radius, 0.0f, m_radius), glm::vec3(0.0f, 0.0f, 1.0f)},
			{glm::vec3(-m_radius, 0.0f, -m_radius), glm::vec3(0.0f, 0.0f, 1.0f)},
			{glm::vec3(m_radius, 0.0f, -m_radius), glm::vec3(0.0f, 0.0f, 1.0f)}
		};
		m_vd.numVertices = sizeof(vertices) / sizeof(Vertex);
		m_vd.vData = new Vertex[m_vd.numVertices];
		memcpy(m_vd.vData, vertices, m_vd.numVertices * sizeof(Vertex));
	}
	void CreateIndices(void)
	{
		unsigned short indices[]
		{
			0, 2, 3, 0, 2, 1
		};
		m_id.numIndices = sizeof(indices) / sizeof(unsigned short);
		m_id.iData = new unsigned short[m_id.numIndices];
		memcpy(m_id.iData, indices, m_id.numIndices * sizeof(unsigned short));
	}
	void InitBuffer(void)
	{
		m_buffer = Buffer<VertexData>(m_vd, m_id);
		m_buffer.Init();
	}
	void GetUniformLocations(void)
	{
		m_locations.proj = glGetUniformLocation(m_shp.ProgramID(), "projection");
		m_locations.view = glGetUniformLocation(m_shp.ProgramID(), "view");
		m_locations.model = glGetUniformLocation(m_shp.ProgramID(), "model");
	}
	void SendUniformData(glm::mat4& proj, glm::mat4& view)
   	{
		glUniformMatrix4fv(m_locations.proj, 1, GL_FALSE, &proj[0][0]);
		glUniformMatrix4fv(m_locations.view, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(m_locations.model, 1, GL_FALSE, &m_translateMatrix[0][0]);
	}
	void ShadersInit(void)
	{
		std::vector<const char*> locations = {"aM_vertexPosition", "aM_vertexColor"};
		m_shp.Compile();
		m_shp.Link(locations);
	}
private:
	glm::mat4 m_translateMatrix;
	float m_radius;
	Buffer<VertexData> m_buffer;
	VertexData m_vd;
	IndexData m_id;
	SHProgram m_shp;
	WaterFrameBuffer m_wfb;
	Locs m_locations;
};

#endif