#ifndef VOLCANO_HEADER
#define VOLCANO_HEADER

#include "biome.h"

class VolcanoBiome
	: public Biome
{
private:
	struct UniformLocations
	{
		signed int projectionLoc;
		signed int viewLoc;
		signed int modelLoc;
		signed int eyePosLoc;
		signed int lightPosLoc;
		signed int timeLoc;
	};
public:
	explicit VolcanoBiome(float maxHeight, VertexData vData, IndexData iData, unsigned int wt, unsigned int ht)
		: m_maxHeight(maxHeight),
		m_lavaShprogram("res\\wavingVsh.shader", "res\\wavingFsh.shader", "res\\wavingGsh.shader"),
		m_indexData(iData)
	{
		m_vertexData.vData = new Vertex[vData.numVertices];
		m_vertexData.numVertices = vData.numVertices;
		memcpy(m_vertexData.vData, vData.vData, vData.numVertices * sizeof(Vertex));

		CalculateElementPosition();
		GetColorOfElements();
		SetLavaPosition(wt, ht);
		LinkLavaShaders();
		GetUniformLocations();
		m_buffer.Init(m_vertexData, m_indexData);
	}
public:
	biome_t BiomeType(void) override
	{
		return Biome::VOLCANO;
	}
	glm::vec3 Color(float y) override
	{
		if (y <= m_lava) return m_obsidianColor;
		else return m_lavaColor;
	}
	void VaryColors(Vertex* v, float* y, unsigned int wt, unsigned int ht) override
	{
		srand(time(NULL));
		unsigned int index = 0;
		for (unsigned int col = 0; col < ht; ++col)
		{
			for (unsigned int row = 0; row < wt; ++row)
			{
				unsigned int varying = rand() % 10;
				
				if (varying == 0)
				{
					unsigned int index1 = col * (ht + 1) + row;
					unsigned int index2 = (col + 1) * (ht + 1) + row;
					unsigned int index3 = (col + 1) * (ht + 1) + row + 1;

					m_vertexData.vData[index].color = m_varyingLavaColor;

					if (v[index1].pos.y <= m_lava || v[index2].pos.y <= m_lava || v[index3].pos.y <= m_lava)
					{
						v[index1].color = m_varyingObsidianColor;
						v[index2].color = m_varyingObsidianColor;
						v[index3].color = m_varyingObsidianColor;
					}
					else
					{
						v[index1].color = m_varyingLavaColor;
						v[index2].color = m_varyingLavaColor;
						v[index3].color = m_varyingLavaColor;
					}
				}

				varying = rand() % 10;
				if (varying == 0)
				{
					unsigned int index4 = col * (ht + 1) + row;
					unsigned int index5 = (col + 1) * (ht + 1) + row + 1;
					unsigned int index6 = col * (ht + 1) + row + 1;

					if (v[index4].pos.y <= m_lava || v[index5].pos.y <= m_lava || v[index6].pos.y <= m_lava)
					{
						v[index4].color = m_varyingObsidianColor;
						v[index5].color = m_varyingObsidianColor;
						v[index6].color = m_varyingObsidianColor;
					}
					else
					{
						v[index4].color = m_varyingLavaColor;
						v[index5].color = m_varyingLavaColor;
						v[index6].color = m_varyingLavaColor;
					}
				}
			}
		}
	}
	glm::vec3 Sky(void) override
	{
		return glm::vec3(0.2f, 0.2f, 0.2f);
	}
	void RenderBiomeElements(glm::mat4& proj, glm::mat4& view, glm::vec3& eyePos, glm::vec3& lightPos, Time* time) override
	{
		m_buffer.BindAll();
		m_lavaShprogram.UseProgram();
		glm::mat4 model = glm::mat4(1.0f);
		SendUniformData(proj, view, model, eyePos, lightPos, (float)(time->currentTime - time->beginning).count() / 1000000000);
		glDrawElements(GL_TRIANGLES, m_indexData.numIndices, GL_UNSIGNED_SHORT, 0);
	}
	void SendAdditionalUniformData(signed int location) override
	{
		glUniform1f(location, m_lava);
	}
protected:
	void CalculateElementPosition(void) override
	{
		m_lava = m_maxHeight * 0.5f;
	}
	void GetColorOfElements(void) override
	{
		m_obsidianColor = glm::vec3(0.0f, 0.0f, 0.02f);
		m_lavaColor = glm::vec3(1.0f, 0.0f, 0.0f);

		m_varyingObsidianColor = glm::vec3(0.05f, 0.0f, 0.1f) * 0.5f;
		m_varyingLavaColor = glm::vec3(1.0f, 69.0f / 255.0f, 0.0f);
	}
	void LinkLavaShaders(void)
	{
		std::vector<std::string> attribLocations = { "aM_vertexPosition", "aM_vertexColor" };
		m_lavaShprogram.Compile();
		m_lavaShprogram.Link(attribLocations);
	}
	void GetUniformLocations(void)
	{
		m_locations.projectionLoc = glGetUniformLocation(m_lavaShprogram.ProgramID(), "u_projectionMatrix");
		m_locations.viewLoc = glGetUniformLocation(m_lavaShprogram.ProgramID(), "u_viewMatrix");
		m_locations.modelLoc = glGetUniformLocation(m_lavaShprogram.ProgramID(), "u_modelMatrix");
		m_locations.eyePosLoc = glGetUniformLocation(m_lavaShprogram.ProgramID(), "u_eyePosition");
		m_locations.lightPosLoc = glGetUniformLocation(m_lavaShprogram.ProgramID(), "u_lightPosition");
		m_locations.timeLoc = glGetUniformLocation(m_lavaShprogram.ProgramID(), "u_time");
	}
	void SendUniformData(glm::mat4& proj, glm::mat4& view, glm::mat4& model, glm::vec3& eyePos, glm::vec3& lightPos, float time)
	{
		glUniformMatrix4fv(m_locations.projectionLoc, 1, GL_FALSE, &proj[0][0]);
		glUniformMatrix4fv(m_locations.viewLoc, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(m_locations.modelLoc, 1, GL_FALSE, &model[0][0]);
		glUniform3fv(m_locations.eyePosLoc, 1, &eyePos[0]);
		glUniform3fv(m_locations.lightPosLoc, 1, &lightPos[0]);
		glUniform1f(m_locations.timeLoc, time);
	}
	// lava mesh that waves
	void SetLavaPosition(unsigned int wt, unsigned int ht)
	{
		for (unsigned int i = 0; i < m_vertexData.numVertices; ++i)
		{
			m_vertexData.vData[i].pos.y = m_maxHeight * 0.25f;
			m_vertexData.vData[i].color = m_lavaColor * 0.8f;
		}

		for (unsigned int col = 0; col < ht; ++col)
		{
			for (unsigned int row = 0; row < wt; ++row)
			{
				unsigned int varying = rand() % 10;
				if (varying == 0)
				{
					unsigned int index1 = col * (ht + 1) + row;
					unsigned int index2 = (col + 1) * (ht + 1) + row;
					unsigned int index3 = (col + 1) * (ht + 1) + row + 1;

					m_vertexData.vData[index1].color = m_varyingLavaColor;
					m_vertexData.vData[index2].color = m_varyingLavaColor;
					m_vertexData.vData[index3].color = m_varyingLavaColor;
				}
				
				varying = rand() % 10;
				if (varying == 0)
				{
					unsigned int index4 = col * (ht + 1) + row;
					unsigned int index5 = (col + 1) * (ht + 1) + row + 1;
					unsigned int index6 = col * (ht + 1) + row + 1;

					m_vertexData.vData[index4].color = m_varyingLavaColor;
					m_vertexData.vData[index5].color = m_varyingLavaColor;
					m_vertexData.vData[index6].color = m_varyingLavaColor;
				}
			}
		}
	}
private:
	float m_lava;

	glm::vec3 m_varyingObsidianColor;
	glm::vec3 m_varyingLavaColor;

	glm::vec3 m_obsidianColor;
	glm::vec3 m_lavaColor;

	float m_maxHeight;

	VertexData m_vertexData;
	IndexData m_indexData;
	SHProgram m_lavaShprogram;
	Buffer m_buffer;
	UniformLocations m_locations;
};

#endif