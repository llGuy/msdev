#define STB_IMAGE_IMPLEMENTATION

#include <math.h>
#include <iostream>
#include <stb-master/stb_image.h>

#include "../heightmap/heightmap.h"
#include "../primitives/vertex.h"
#include "terrain.h"

#include "../biome/snow.h"
#include "../biome/volcano.h"
#include "../biome/planes.h"
#include "../biome/desert.h"

static float BarryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) {
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

Terrain::Terrain(float dimX, float dimY, float maxHeight, Biome::biome_t biome)
	: m_width(dimX), m_height(dimY), m_shprogram("res\\vsh.shader", "res\\fsh.shader", "res\\gsh.shader"),
	m_lightPosition(0.0f, 10.0f, 0.0f), m_maxHeight(maxHeight)
{
	InitHeightmap();
	ComputeTerrainType();
	GenerateTerrainVerts();
	GenerateTerrainIndices();
	InitBiome(biome);
	GenerateColors();
	m_biome->VaryColors(m_vertices, m_yVals, m_numTilesWidth, m_numTilesHeight);

	InitBuffer();
	CompileShaders();
	GetUniformLocations();
}
Terrain::~Terrain(void)
{
	delete[] m_vertices;
	delete[] m_indices;
	delete[] m_yVals;
}
void Terrain::Draw(glm::mat4& projMat, glm::mat4& viewMat, glm::vec3& eyePos)
{
	m_buffer->BindAll();
	glm::mat4 modelMat = glm::mat4(1.0f);
	SendUniformData(projMat, viewMat, modelMat, eyePos);
	glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_SHORT, 0);
}
glm::vec3 Terrain::Sky(void)
{
	return m_biome->Sky();
}
void Terrain::InitializeHeights(void)
{
	m_yVals = new float[m_numVertices];
	m_hm->ComputeHeights(m_yVals, m_numVertsWidth, m_numVertsHeight, m_maxHeight);
}
void Terrain::GenerateTerrainVerts(void)
{
	//computing the halfs
	m_widthHalf = m_width / 2;			// make the terrain centered
	m_heightHalf = m_height / 2;
	//computing the number of vertices
	m_numVertsWidth = m_width + 1;
	m_numVertsHeight = m_height + 1;
	//computing the number of squares / tiles
	m_numTilesWidth = m_numVertsWidth - 1;
	m_numTilesHeight = m_numVertsHeight - 1;

	m_numVertices = m_numVertsWidth * m_numVertsHeight;
	m_vertices = new Vertex[m_numVertices];
	InitializeHeights();
	for (unsigned int col = 0; col < m_numVertsHeight; ++col)
	{
		for (unsigned int row = 0; row < m_numVertsWidth; ++row)
		{
			unsigned int index = row + m_numVertsHeight * col;		// should be m_numVertsWidth
			
			Vertex vert;

			float x = row - m_widthHalf;
			float y = m_yVals[index];
			float z = col - m_heightHalf;

			vert.pos = glm::vec3(x, y, z);

			m_vertices[index].pos = vert.pos;
		}
	}
}
void Terrain::GenerateTerrainIndices(void)
{
	auto getNumIndices = [&](void)->unsigned int { 
		return ((m_numVertsWidth - 1) * 6) * (m_numVertsHeight - 1); };
	m_numIndices = getNumIndices();
	unsigned int index = 0;
	m_indices = new unsigned short[m_numIndices];

	for (unsigned int col = 0; col < m_numTilesHeight; ++col)
	{
		for (unsigned int row = 0; row < m_numTilesWidth; ++row)
		{
			m_indices[index++] = col * m_numVertsHeight + row;
			m_indices[index++] = (col + 1) * m_numVertsHeight + row;
			m_indices[index++] = (col + 1) * m_numVertsHeight + row + 1;

			m_indices[index++] = col * m_numVertsHeight + row;
			m_indices[index++] = (col + 1) * m_numVertsHeight + row + 1;
			m_indices[index++] = col * m_numVertsHeight + row + 1;			
		}
	}
}
void Terrain::GenerateColors(void)
{
	for (unsigned int col = 0; col < m_numTilesHeight; ++col)
	{
		for (unsigned int row = 0; row < m_numTilesWidth; ++row)
		{
			unsigned int index = row + m_numVertsHeight * col;
			m_vertices[index].color = m_biome->Color(m_yVals[index]);
		}
	}
}
float Terrain::GetYPosOfPlayer(float x, float z, float debug)
{
	// create terrain coordinate system
	float tx = abs(x - (m_widthHalf - m_width));
	float tz = abs(z - (m_heightHalf - m_height));

	// which tile in player 
	float tileX = floor(tx);
	float tileZ = floor(tz);

	float posOfPlayerOnTileX = tx - tileX;
	float posOfPlayerOnTileZ = tz - tileZ;

	float height;
	if (posOfPlayerOnTileZ <= 1 - posOfPlayerOnTileX)
	{
		unsigned int ind1 = tileZ * m_numVertsHeight + tileX;
		unsigned int ind2 = (tileZ + 1) * m_numVertsHeight + tileX;
		unsigned int ind3 = (tileZ + 1) * m_numVertsHeight + tileX + 1;

		glm::vec2 positionOfPlayer = glm::vec2(posOfPlayerOnTileX, posOfPlayerOnTileZ - 1.0f);
		float m_yVal1 = m_yVals[ind1];
		float m_yVal2 = m_yVals[ind2];
		float m_yVal3 = m_yVals[ind3];
		height = BarryCentric(glm::vec3(0.0f, m_yVal1, 0.0f), glm::vec3(0.0f, m_yVal2, -1.0f),
			glm::vec3(1.0f, m_yVal3, -1.0f), positionOfPlayer);

		if (abs(height - (debug - 0.7f)) > 0.1f)
		{
			std::cout << "bug" << std::endl;
		}

		ind1 = tileZ * m_numVertsHeight + tileX;
		ind2 = (tileZ + 1) * m_numVertsHeight + tileX;
		ind3 = (tileZ + 1) * m_numVertsHeight + tileX + 1;

		positionOfPlayer = glm::vec2(posOfPlayerOnTileX, posOfPlayerOnTileZ - 1.0f);
		m_yVal1 = m_yVals[ind1];
		m_yVal2 = m_yVals[ind2];
		m_yVal3 = m_yVals[ind3];
		height = BarryCentric(glm::vec3(0.0f, m_yVal1, 0.0f), glm::vec3(0.0f, m_yVal2, -1.0f),
			glm::vec3(1.0f, m_yVal3, -1.0f), positionOfPlayer);
	}
	else
	{
		unsigned int ind1 = tileZ * m_numVertsHeight + tileX;
		unsigned int ind2 = (tileZ + 1) * m_numVertsHeight + tileX + 1;
		unsigned int ind3 = tileZ * m_numVertsHeight + tileX + 1;

		glm::vec2 positionOfPlayer = glm::vec2(posOfPlayerOnTileX, posOfPlayerOnTileZ - 1.0f);
		float m_yVal1 = m_yVals[ind1];
		float m_yVal2 = m_yVals[ind2];
		float m_yVal3 = m_yVals[ind3];
		height = BarryCentric(glm::vec3(0.0f, m_yVals[ind1], 0.0f), glm::vec3(1.0f, m_yVals[ind2], -1.0f),
			glm::vec3(1.0f, m_yVals[ind3], 0.0f), positionOfPlayer);
	}

	return height;
}
void Terrain::CompileShaders(void)
{
	m_shprogram.Compile();
	m_shprogram.Link();
}
void Terrain::GetUniformLocations(void)
{
	m_uniformLocations.m_uniLocProjection = glGetUniformLocation(m_shprogram.ProgramID(), "u_projectionMatrix");
	m_uniformLocations.m_uniLocView = glGetUniformLocation(m_shprogram.ProgramID(), "u_viewMatrix");
	m_uniformLocations.m_uniLocModel = glGetUniformLocation(m_shprogram.ProgramID(), "u_modelMatrix");
	m_uniformLocations.m_uniLocLightPosition = glGetUniformLocation(m_shprogram.ProgramID(), "u_lightPosition");
	m_uniformLocations.m_uniLocEyePosition = glGetUniformLocation(m_shprogram.ProgramID(), "u_eyePosition");
}
void Terrain::SendUniformData(glm::mat4& proj, glm::mat4& view, glm::mat4& model, glm::vec3& eyePos)
{
	glUniformMatrix4fv(m_uniformLocations.m_uniLocProjection, 1, GL_FALSE, &proj[0][0]);
	glUniformMatrix4fv(m_uniformLocations.m_uniLocView, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(m_uniformLocations.m_uniLocModel, 1, GL_FALSE, &model[0][0]);
	glUniform3fv(m_uniformLocations.m_uniLocLightPosition, 1, &m_lightPosition[0]);
	glUniform3fv(m_uniformLocations.m_uniLocEyePosition, 1, &eyePos[0]);
}
void Terrain::ComputeTerrainType(void) 
{
	m_dirtLimit = m_maxHeight / 3;
	m_rockStart = m_maxHeight / 5 * 3;
	m_snowStart = m_maxHeight - m_maxHeight / 5;
}
void Terrain::InitBuffer(void) 
{
	m_buffer = new Buffer(m_vertices, m_indices, m_numVertices, m_numIndices);
	m_buffer->Init();
}
void Terrain::InitHeightmap(void)
{
	m_hm = new Heightmap("C:\\Users\\lucro\\Development\\msdev\\Terrain\\Debug\\terrain1.png");
}
void Terrain::InitBiome(Biome::biome_t biome)
{
	if (biome == Biome::SNOW)
		m_biome = new SnowBiome(m_maxHeight);
	else if (biome == Biome::VOLCANO)
		m_biome = new VolcanoBiome(m_maxHeight);
	else if (biome == Biome::PLANES)
		m_biome = new PlanesBiome(m_maxHeight);
	else if (biome == Biome::DESERT)
		m_biome = new DesertBiome(m_maxHeight);
}