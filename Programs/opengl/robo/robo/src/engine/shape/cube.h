#ifndef CUBE_HEADER
#define CUBE_HEADER

#include "shape.h"
#include "../data/time.h"
#include "../engine.h"

class Cube final
	: public Shape
{
public:
	explicit Cube(float rad, glm::vec3 color, const bool elevate)
		: m_cubeRadius(rad), m_color(color), m_elevate(elevate)
	{
	}
	void Draw(glm::mat4& proj, glm::mat4& view, glm::mat4& model,
		glm::vec3& eyePos, glm::vec3& lightPos, UniformLocations* locations,
		Time* timeData) override
	{
		m_buffer.BindAll();
		UniformData(proj, view, model, eyePos, lightPos, timeData, locations);
		glDrawElements(GL_TRIANGLES, m_buffer.NumIndices(), GL_UNSIGNED_SHORT, 0);
	}
	void Init(void) override
	{
		VerticesInit();
		IndicesInit();
		BufferInit();

		DeleteRAM();
	}
protected:
	void VerticesInit(void) override
	{
		Vertex stackVerts[] = {
			{ glm::vec3(-m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 0
			m_color }, // Color
		{ glm::vec3(+m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 1
		m_color }, // Color
		{ glm::vec3(+m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 2
		m_color }, // Color
		{ glm::vec3(-m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 3
		m_color }, // Color

		{ glm::vec3(-m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 4
		m_color }, // Color
		{ glm::vec3(+m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 5
		m_color }, // Color
		{ glm::vec3(+m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 6
		m_color }, // Color
		{ glm::vec3(-m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 7
		m_color }, // Color

		{ glm::vec3(+m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 8
		m_color }, // Color
		{ glm::vec3(+m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 9
		m_color }, // Color
		{ glm::vec3(+m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 10
		m_color }, // Color
		{ glm::vec3(+m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 11
		m_color }, // Color

		{ glm::vec3(-m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 12
		m_color }, // Color
		{ glm::vec3(-m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 13
		m_color }, // Color
		{ glm::vec3(-m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 14
		m_color }, // Color
		{ glm::vec3(-m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 15
		m_color }, // Color

		{ glm::vec3(+m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 16
		m_color }, // Color
		{ glm::vec3(-m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 17
		m_color }, // Color
		{ glm::vec3(-m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 18
		m_color }, // Color
		{ glm::vec3(+m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 19
		m_color }, // Color

		{ glm::vec3(+m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 20
		m_color }, // Color
		{ glm::vec3(-m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 21
		m_color }, // Color
		{ glm::vec3(-m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 22
		m_color }, // Color
		{ glm::vec3(+m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 23
		m_color }, // Color
		};
		m_vd.numVertices = sizeof(stackVerts) / sizeof(Vertex);
		m_vd.vData = new Vertex[m_vd.numVertices];
		memcpy(m_vd.vData, stackVerts, sizeof(Vertex) * m_vd.numVertices);
		if(m_elevate)
			for (unsigned short i = 0; i < m_vd.numVertices; ++i)
				m_vd.vData[i].pos.y += m_cubeRadius;
	}
	void IndicesInit(void) override
	{
		unsigned short indices[]
		{
			0,   1,  2,  0,  2,  3, // Top
			4,   5,  6,  4,  6,  7, // Front
			8,   9, 10,  8, 10, 11, // Right
			12, 13, 14, 12, 14, 15, // Left
			16, 17, 18, 16, 18, 19, // Back
			20, 22, 21, 20, 23, 22, // Bottom
		};

		m_id.numIndices = sizeof(indices) / sizeof(unsigned short);
		m_id.iData = new unsigned short[m_id.numIndices];
		memcpy(m_id.iData, indices, sizeof(unsigned short) * m_id.numIndices);
	}
	void BufferInit(void) override
	{	
		m_buffer = Buffer(m_vd, m_id);
	}
	void DeleteRAM(void) override
	{
		delete[] m_vd.vData;
		delete[] m_id.iData;
	}

	void UniformData(glm::mat4& proj, glm::mat4& view, glm::mat4& model,
		glm::vec3& eyePos, glm::vec3& lightPos,
		Time* timeData, UniformLocations* locations) override
	{
		glUniformMatrix4fv(locations->m_uniLocProjection, 1, GL_FALSE, &proj[0][0]);
		glUniformMatrix4fv(locations->m_uniLocView, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(locations->m_uniLocModel, 1, GL_FALSE, &model[0][0]);
		glUniform3fv(locations->m_uniLocLightPosition, 1, &lightPos[0]);
		glUniform3fv(locations->m_uniLocEyePosition, 1, &eyePos[0]);
		glUniform1f(locations->m_uniLocTime, (float)(timeData->currentTime - timeData->beginning).count() / 1000000000);
	}
protected:
	glm::vec3 m_color;
	float m_cubeRadius;
	bool m_elevate;
};

#endif