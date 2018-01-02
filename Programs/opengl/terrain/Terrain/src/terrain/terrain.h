#ifndef TERRAIN_HEADER
#define TERRAIN_HEADER

#include <glm/glm.hpp>

#include "../shader/shprogram.h"

struct Vertex;

class Terrain
{
public:
	explicit Terrain(float dimRow, float dimCol, float);
	~Terrain(void);

	void Draw(glm::mat4& mvp, glm::mat4& viewMat);
private:
	void GenerateTerrainVerts(void);
	void GenerateTerrainIndices(void);
	void InitializeHeights(void);
private:
	void SendVerticesToGPU(void);
	void SendIndicesToGPU(void);
	void CreateVertexArray(void);
	void CompileShaders(void);
	void ReadImage(void);
	void GetUniformLocations(void);
	void SendUniformData(glm::mat4& proj, glm::mat4& view, glm::mat4& model);
	void ComputeTerrainType();
private:
	typedef unsigned int uint32;
	typedef unsigned char uint8;
	typedef unsigned short uint16;

	//dimRow
	float m_width;					// dimentions
	float m_height;

	float m_dirtLimit;
	float m_rockStart;
	float m_snowStart;

	unsigned short* m_indices;
	Vertex* m_vertices;

	unsigned int m_numVertices;
	unsigned int m_numIndices;

	glm::vec3 m_ambientColorDirt;
	glm::vec3 m_ambientColorGrass;
	glm::vec3 m_ambientColorRock;
	glm::vec3 m_ambientColorSnow;
	glm::vec3 m_lightPosition;

	float* m_yVals;
	float m_maxHeight;

	//m_numTilesVertsRow, Col
	unsigned int m_numVertsWidth;
	unsigned int m_numVertsHeight;

	unsigned int m_numTilesWidth;
	unsigned int m_numTilesHeight;

	float m_widthHalf;
	float m_heightHalf;

	SHProgram m_shprogram;

	unsigned int m_vertexBufferID;
	unsigned int m_indexBufferID;
	unsigned int m_vaoID;

	unsigned int m_vertexDataSize;
	unsigned int m_indexDataSize;

	signed int m_uniformLocationModel;
	signed int m_uniformLocationProjection;
	signed int m_uniformLocationView;
	signed int m_uniformLocationLightPosition;
};

#endif