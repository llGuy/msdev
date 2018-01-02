#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <stb-master/stb_image.h>

#include "../primitives/vertex.h"
#include "terrain.h"

Terrain::Terrain(float dimX, float dimY, glm::vec3 color)
	: m_width(dimX), m_height(dimY), m_color(color), m_shprogram("res\\vsh.shader", "res\\fsh.shader")
{
	GenerateTerrainVerts();
	GenerateTerrainIndices();

	SendVerticesToGPU();
	SendIndicesToGPU();
	CreateVertexArray();
	CompileShaders();
}
Terrain::~Terrain(void)
{
}
void Terrain::Draw(glm::mat4& mvp)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glBindVertexArray(m_vaoID);

	m_uniformLocationMVP = glGetUniformLocation(m_shprogram.ProgramID(), "u_mvp");
	glUniformMatrix4fv(m_uniformLocationMVP, 1, GL_FALSE, &mvp[0][0]);

	glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_SHORT, 0);
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

			vert.norm = glm::vec3(x, y, z);
			//color
			//vert.color = glm::vec3(m_color.r, m_color.g, m_color.b);
			
			m_vertices[index].pos = vert.pos;
			m_vertices[index].norm = vert.norm;
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
}
void Terrain::GetUniformLocations(void)
{
	m_uniformLocationMVP = glGetUniformLocation(m_shprogram.ProgramID(), "mvp");
}
void Terrain::CompileShaders(void)
{
	m_shprogram.Compile();
	m_shprogram.Link();
}
void Terrain::ReadImage(void)
{
	float MAX_HEIGHT = 20;

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
			float height = (float)grayScale / 0b11111111 * MAX_HEIGHT;
			m_yVals[row + col * m_numVertsHeight] = height;
			m_vertices[row + col * m_numVertsHeight].color = glm::vec3(height / MAX_HEIGHT);
		}

	}
}