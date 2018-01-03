#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <stb-master/stb_image.h>

#include "../primitives/vertex.h"
#include "terrain.h"

Terrain::Terrain(float dimX, float dimY, float maxHeight)
	: m_width(dimX), m_height(dimY), m_shprogram("res\\vsh.shader", "res\\fsh.shader", "res\\gsh.shader"),
	m_ambientColorGrass(0.1f, 0.3f, 0.1f), m_ambientColorDirt(0.25, 0.175, 0.025), m_ambientColorSnow(0.4f, 0.4f, 0.4f),
	m_ambientColorRock(0.2f, 0.2f, 0.2f),
	m_lightPosition(0.0f, 10.0f, 0.0f), m_maxHeight(maxHeight)
{
	ComputeTerrainType();
	GenerateTerrainVerts();
	GenerateTerrainIndices();

	SendVerticesToGPU();
	SendIndicesToGPU();
	CreateVertexArray();
	CompileShaders();
	GetUniformLocations();
}
Terrain::~Terrain(void)
{
}
void Terrain::Draw(glm::mat4& projMat, glm::mat4& viewMat, glm::vec3& eyePos)
{
	//m_lightPosition = eyePos;
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glBindVertexArray(m_vaoID);

	glm::mat4 modelMat = glm::mat4(1.0f);

	SendUniformData(projMat, viewMat, modelMat, eyePos);

	glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_SHORT, 0);
	//m_lightPosition.y -= 0.001f;
}
void Terrain::InitializeHeights(void)
{
	ReadImage();
}
void Terrain::GenerateTerrainVerts(void)
{
	m_widthHalf = m_width / 2;			// make the terrain centered
	m_heightHalf = m_height / 2;
	m_numVertsWidth = m_width + 1;
	m_numVertsHeight = m_height + 1;
	m_numTilesWidth = m_numVertsWidth - 1;
	m_numTilesHeight = m_numVertsHeight - 1;
	m_numVertices = m_numVertsWidth * m_numVertsHeight;
	m_vertices = new Vertex[m_numVertices];
	m_yVals = new float[m_numVertices];
	InitializeHeights();

	for (unsigned int col = 0; col < m_numVertsHeight; ++col)
	{
		for (unsigned int row = 0; row < m_numVertsWidth; ++row)
		{
			unsigned int index = row + m_numVertsHeight * col;		// should be m_numVertsWidth
			Vertex vert;
			//position
			float x = row - m_widthHalf;
			float y = m_yVals[index];
			float z = col - m_heightHalf;

			vert.pos = glm::vec3(x, y, z);
			//normal
			x = 0.0f;
			y = 1.0f;
			z = 0.0f;

			//vert.norm = glm::vec3(x, y, z);
			//color
			if (m_yVals[index] <= m_dirtLimit)
			{
				vert.color = m_ambientColorDirt;
			}
			else if (m_yVals[index] > m_dirtLimit && m_yVals[index] <= m_rockStart)
			{
				vert.color = m_ambientColorGrass;
			}
			else if (m_yVals[index] > m_rockStart && m_yVals[index] <= m_snowStart)
			{
				vert.color = m_ambientColorRock;
			}
			else if (m_yVals[index] > m_snowStart)
			{
				vert.color = m_ambientColorSnow;
			}
			
			m_vertices[index].pos = vert.pos;
			m_vertices[index].color = vert.color;
			//m_vertices[index].norm = vert.norm;
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
			unsigned short i1 = col * m_numVertsHeight + row;
			unsigned short i2 = (col + 1) * m_numVertsHeight + row;
			unsigned short i3 = (col + 1) * m_numVertsHeight + row + 1;
			unsigned short i4 = col * m_numVertsHeight + row;
			unsigned short i5 = (col + 1) * m_numVertsHeight + row + 1;
			unsigned short i6 = col * m_numVertsHeight + row + 1;

			m_indices[index] = i1;
			++index;
			m_indices[index] = i2;
			++index;
			m_indices[index] = i3;
			++index;

			m_indices[index] = i4;
			++index;
			m_indices[index] = i5;
			++index;
			m_indices[index] = i6;
			++index;
		}
	}
}

void Terrain::SendVerticesToGPU(void)
{
	m_vertexDataSize = m_numVertices * sizeof(Vertex);

	glGenBuffers(1, &m_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, m_vertexDataSize, m_vertices, GL_STATIC_DRAW);
}

void Terrain::SendIndicesToGPU(void)
{
	m_indexDataSize = m_numIndices * sizeof(unsigned short);

	glGenBuffers(1, &m_indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexDataSize, m_indices, GL_STATIC_DRAW);
}

void Terrain::CreateVertexArray(void)
{
	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
}
void Terrain::CompileShaders(void)
{
	m_shprogram.Compile();
	m_shprogram.Link();
}
void Terrain::ReadImage(void)
{
	//load image
	int width, height, nrChannels;
	uint8* data = stbi_load("C:\\Users\\lucro\\Development\\msdev\\Terrain\\Debug\\terrain1.png", 
		&width, &height, &nrChannels, 0);
	uint32 sizeOfImage = width * height;
	
	unsigned int strideWidth = width * 3 / m_numVertsWidth;
	unsigned int strideHeight = height / m_numVertsHeight;

	unsigned int imageIndexRow;
	unsigned int imageIndexHeight;
	unsigned int imageIndex;

	for (unsigned int col = 0; col < m_numVertsHeight; ++col)
	{
		for (unsigned int row = 0; row < m_numVertsWidth; ++row)
		{
			imageIndexRow = strideWidth * row;
			imageIndexHeight = strideHeight * col * (width * 3);

			imageIndex = imageIndexRow + imageIndexHeight;

			unsigned char grayScale = data[imageIndex];
			float height = (float)grayScale / 0b11111111 * m_maxHeight;
			m_yVals[row + col * m_numVertsHeight] = height;
			//m_vertices[row + col * m_numVertsHeight].color = glm::vec3(height / MAX_HEIGHT);
		}
	}
}
void Terrain::GetUniformLocations(void)
{
	m_uniformLocationProjection = glGetUniformLocation(m_shprogram.ProgramID(), "u_projectionMatrix");
	m_uniformLocationView = glGetUniformLocation(m_shprogram.ProgramID(), "u_viewMatrix");
	m_uniformLocationModel = glGetUniformLocation(m_shprogram.ProgramID(), "u_modelMatrix");
	m_uniformLocationLightPosition = glGetUniformLocation(m_shprogram.ProgramID(), "u_lightPosition");
	m_uniformLocationEyePosition = glGetUniformLocation(m_shprogram.ProgramID(), "u_eyePosition");
}
void Terrain::SendUniformData(glm::mat4& proj, glm::mat4& view, glm::mat4& model, glm::vec3& eyePos)
{
	glUniformMatrix4fv(m_uniformLocationProjection, 1, GL_FALSE, &proj[0][0]);
	glUniformMatrix4fv(m_uniformLocationView, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(m_uniformLocationModel, 1, GL_FALSE, &model[0][0]);
	glUniform3fv(m_uniformLocationLightPosition, 1, &m_lightPosition[0]);
	glUniform3fv(m_uniformLocationEyePosition, 1, &eyePos[0]);
}
void Terrain::ComputeTerrainType(void) 
{
	m_dirtLimit = m_maxHeight / 3;
	m_rockStart = m_maxHeight / 5 * 3;
	m_snowStart = m_maxHeight - m_maxHeight / 5;
}