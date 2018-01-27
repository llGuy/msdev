#ifndef CUBE_HEADER
#define CUBE_HEADER

#include "../texture/texture.h"
#include "../buffer/buffer.h"
#include "../data/vertex_data.h"
#include "../data/uni_loc_and_data.h"
#include <glm/glm.hpp>

class Cube
{
public:
	explicit Cube(void) = default;
	explicit Cube(float radius)
		: m_cubeRadius(radius)
	{
		CreateVertices();
		CreateIndices();
		BufferInit();
		DeleteRAMData();
	}
	void Draw(glm::mat4& proj, glm::mat4& view, glm::mat4& model,
		glm::vec3& eyePosition, glm::vec3& lightPosition, UniformLocations* locations)
	{
		m_buffer.BindAll();
		UniformData(proj, view, model, eyePosition, lightPosition, locations);
		glDrawElements(GL_TRIANGLES, m_buffer.NumIndices(), GL_UNSIGNED_SHORT, 0);
	}
private:
	void CreateVertices(void)
	{
		TVertex stackVerts[] = {
			{ glm::vec3(-m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 0
			glm::vec2(0.0f, 1.0f) }, // Color
		{ glm::vec3(+m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 1
		glm::vec2(1.0f, 1.0f) }, // Color
		{ glm::vec3(+m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 2
		glm::vec2(1.0f, 0.0f) }, // Color
		{ glm::vec3(-m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 3
		glm::vec2(0.0f, 0.0f) }, // Color

		{ glm::vec3(-m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 4
		glm::vec2(0.0f, 0.0f) }, // Color
		{ glm::vec3(+m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 5
		glm::vec2(1.0f, 0.0f) }, // Color
		{ glm::vec3(+m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 6
		glm::vec2(1.0f, 1.0f) }, // Color
		{ glm::vec3(-m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 7
		glm::vec2(0.0f, 1.0f) }, // Color

		{ glm::vec3(+m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 8
		glm::vec2(1.0f, 0.0f) }, // Color
		{ glm::vec3(+m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 9
		glm::vec2(0.0f, 0.0f) }, // Color
		{ glm::vec3(+m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 10
		glm::vec2(0.0f, 1.0f) }, // Color
		{ glm::vec3(+m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 11
		glm::vec2(1.0f, 1.0f) }, // Color

		{ glm::vec3(-m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 12
		glm::vec2(1.0f, 0.0f) }, // Color
		{ glm::vec3(-m_cubeRadius, +m_cubeRadius, -m_cubeRadius), // 13
		glm::vec2(0.0f, 0.0f) }, // Color
		{ glm::vec3(-m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 14
		glm::vec2(0.0f, 1.0f) }, // Color
		{ glm::vec3(-m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 15
		glm::vec2(1.0f, 1.0f) }, // Color

		{ glm::vec3(+m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 16
		glm::vec2(0.0f, 0.0f) }, // Color
		{ glm::vec3(-m_cubeRadius, +m_cubeRadius, +m_cubeRadius), // 17
		glm::vec2(1.0f, 0.0f) }, // Color
		{ glm::vec3(-m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 18
		glm::vec2(1.0f, 1.0f) }, // Color
		{ glm::vec3(+m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 19
		glm::vec2(0.0f, 1.0f) }, // Color

		{ glm::vec3(+m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 20
		glm::vec2(0.0f, 1.0f) }, // Color
		{ glm::vec3(-m_cubeRadius, -m_cubeRadius, -m_cubeRadius), // 21
		glm::vec2(1.0f, 1.0f) }, // Color
		{ glm::vec3(-m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 22
		glm::vec2(1.0f, 0.0f) }, // Color
		{ glm::vec3(+m_cubeRadius, -m_cubeRadius, +m_cubeRadius), // 23
		glm::vec2(0.0f, 0.0f) }, // Color
		};      
		m_tdata.numVertices = sizeof(stackVerts) / sizeof(TVertex);
		m_tdata.vData = new TVertex[m_tdata.numVertices];
		memcpy(m_tdata.vData, stackVerts, sizeof(TVertex) * m_tdata.numVertices);

		/*TVertex stackVerts[]
		{
			// face 1 +z
			glm::vec3(-m_cubeRadius, +m_cubeRadius, +m_cubeRadius),		//1
			glm::vec2(0.0f, 0.0f),
			glm::vec3(+m_cubeRadius, +m_cubeRadius, +m_cubeRadius),		//2
			glm::vec2(1.0f, 0.0f),
			glm::vec3(+m_cubeRadius, -m_cubeRadius, +m_cubeRadius),		//3
			glm::vec2(1.0f, 1.0f),

			glm::vec3(-m_cubeRadius, +m_cubeRadius, +m_cubeRadius),		//4
			glm::vec2(0.0f, 0.0f),
			glm::vec3(+m_cubeRadius, -m_cubeRadius, +m_cubeRadius),		//5
			glm::vec2(1.0f, 1.0f),
			glm::vec3(-m_cubeRadius, -m_cubeRadius, +m_cubeRadius),		//6
			glm::vec2(0.0f, 1.0f),
			//face 2 +x
			glm::vec3(+m_cubeRadius, +m_cubeRadius, -m_cubeRadius),		//7
			glm::vec2(1.0f, 0.0f),
			glm::vec3(+m_cubeRadius, -m_cubeRadius, -m_cubeRadius),		//8
			glm::vec2(1.0f, 1.0f),
			glm::vec3(+m_cubeRadius, -m_cubeRadius, +m_cubeRadius),		//9
			glm::vec2(0.0f, 1.0f),

			glm::vec3(+m_cubeRadius, +m_cubeRadius, +m_cubeRadius),		//10
			glm::vec2(0.0f, 0.0f),
			glm::vec3(+m_cubeRadius, -m_cubeRadius, +m_cubeRadius),		//11
			glm::vec2(0.0f, 1.0f),
			glm::vec3(+m_cubeRadius, +m_cubeRadius, -m_cubeRadius),		//12
			glm::vec2(1.0f, 0.0f),
			//face 3 +y
			glm::vec3(+m_cubeRadius, +m_cubeRadius, +m_cubeRadius),		//13
			glm::vec2(0.0f, 0.0f),
			glm::vec3(+m_cubeRadius, +m_cubeRadius, -m_cubeRadius),		//14
			glm::vec2(1.0f, 0.0f),
			glm::vec3(-m_cubeRadius, +m_cubeRadius, -m_cubeRadius),		//15
			glm::vec2(1.0f, 1.0f),

			glm::vec3(+m_cubeRadius, +m_cubeRadius, +m_cubeRadius),		//16
			glm::vec2(0.0f, 0.0f),
			glm::vec3(-m_cubeRadius, +m_cubeRadius, -m_cubeRadius),		//17
			glm::vec2(1.0f, 1.0f),
			glm::vec3(-m_cubeRadius, +m_cubeRadius, +m_cubeRadius),		//18
			glm::vec2(0.0f, 1.0f),
			//face 4 -z
			glm::vec3(+m_cubeRadius, -m_cubeRadius, -m_cubeRadius),		//19
			glm::vec2(0.0f, 0.0f),
			glm::vec3(+m_cubeRadius, +m_cubeRadius, -m_cubeRadius),		//20
			glm::vec2(1.0f, 0.0f),
			glm::vec3(-m_cubeRadius, +m_cubeRadius, -m_cubeRadius),		//21
			glm::vec2(1.0f, 1.0f),

			glm::vec3(+m_cubeRadius, -m_cubeRadius, -m_cubeRadius),		//22
			glm::vec2(0.0f, 0.0f),
			glm::vec3(-m_cubeRadius, +m_cubeRadius, -m_cubeRadius),		//23
			glm::vec2(1.0f, 1.0f),
			glm::vec3(-m_cubeRadius, -m_cubeRadius, -m_cubeRadius),		//24
			glm::vec2(0.0f, 1.0f),
			//face 5 -x
			glm::vec3(-m_cubeRadius, +m_cubeRadius, -m_cubeRadius),		//25
			glm::vec2(1.0f, 0.0f),
			glm::vec3(-m_cubeRadius, -m_cubeRadius, -m_cubeRadius),
			glm::vec2(1.0f, 1.0f),
			glm::vec3(-m_cubeRadius, -m_cubeRadius, +m_cubeRadius),
			glm::vec2(0.0f, 1.0f),

			glm::vec3(-m_cubeRadius, +m_cubeRadius, +m_cubeRadius),
			glm::vec2(0.0f, 0.0f),
			glm::vec3(-m_cubeRadius, -m_cubeRadius, +m_cubeRadius),
			glm::vec2(0.0f, 1.0f),
			glm::vec3(-m_cubeRadius, +m_cubeRadius, -m_cubeRadius),
			glm::vec2(1.0f, 0.0f),
			//face 6 -y
			glm::vec3(-m_cubeRadius, -m_cubeRadius, -m_cubeRadius),
			glm::vec2(0.0f, 0.0f),
			glm::vec3(-m_cubeRadius, -m_cubeRadius, +m_cubeRadius),
			glm::vec2(1.0f, 0.0f),
			glm::vec3(+m_cubeRadius, -m_cubeRadius, +m_cubeRadius),
			glm::vec2(1.0f, 1.0f),

			glm::vec3(-m_cubeRadius, -m_cubeRadius, -m_cubeRadius),
			glm::vec2(0.0f, 0.0f),
			glm::vec3(+m_cubeRadius, -m_cubeRadius, +m_cubeRadius),
			glm::vec2(1.0f, 1.0f),
			glm::vec3(+m_cubeRadius, -m_cubeRadius, -m_cubeRadius),
			glm::vec2(0.0f, 1.0f),
		};
		m_tdata.numVertices = sizeof(stackVerts) / sizeof(TVertex);
		m_tdata.vData = new TVertex[m_tdata.numVertices];
		memcpy(m_tdata.vData, stackVerts, sizeof(TVertex) * m_tdata.numVertices);*/
	}
	void GenerateTextureCoordinate(void)
	{
		glm::vec2 plus[] {glm::vec2(0.0f, 1.0f), glm::vec2(), glm::vec2(), glm::vec2(0.0f)};
		for (unsigned int i = 0; i < m_tdata.numVertices / 6; ++i)
		{

		}
	}
	void CreateIndices(void)
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
		
		/*unsigned short indices[]
		{
			0, 1, 2, 3, 4, 5,
			6, 7, 8, 9, 10, 11,
			12, 13, 14, 15, 16, 17,
			18, 19, 20, 21, 22, 23,
			24, 25, 26, 27, 28, 29,
			30, 31, 32, 33, 34, 35
		};*/
		m_id.numIndices = sizeof(indices) / sizeof(unsigned short);
		m_id.iData = new unsigned short[m_id.numIndices];
		memcpy(m_id.iData, indices, sizeof(unsigned short) * m_id.numIndices);
	}
	void BufferInit(void)
	{
		m_buffer = Buffer<TexturedData>(m_tdata, m_id);
		m_buffer.Init(true);
	}
	void DeleteRAMData(void)
	{
		delete[] m_tdata.vData;
		delete[] m_id.iData;
	}
	void UniformData(glm::mat4& proj, glm::mat4& view, glm::mat4& model, 
		glm::vec3& eyePosition, glm::vec3& lightPosition, UniformLocations* locations)
	{
		glUniformMatrix4fv(locations->m_uniLocProjection, 1, GL_FALSE, &proj[0][0]);
		glUniformMatrix4fv(locations->m_uniLocView, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(locations->m_uniLocModel, 1, GL_FALSE, &model[0][0]);
		glUniform3fv(locations->m_uniLocLightPosition, 1, &lightPosition[0]);
		glUniform3fv(locations->m_uniLocEyePosition, 1, &eyePosition[0]);
	}
private:
	TexturedData m_tdata;
	IndexData m_id;
	Buffer<TexturedData> m_buffer;
	float m_cubeRadius;
};

#endif