#ifndef TERRAIN_HEADER
#define TERRAIN_HEADER

#include <glm/glm.hpp>

#include "../shader/shprogram.h"
#include "../buffer/buffer.h"

#include "../heightmap/heightmap.h"
#include "../data/vertex_data.h"
#include "../data/uni_loc_and_data.h"
#include "../data/index_data.h"

class Terrain
{
public:
	struct TerrainDimensions
	{
		float x;
		float z;
		float yMax;
	};
	struct MeshData
	{
		float* y;

		VertexData vertices;
		IndexData indices;

		unsigned int xNumVerts, zNumVerts;
		unsigned int xNumTiles, zNumTiles;
		float xHalf, zHalf;
	};
	

	explicit Terrain(Terrain::TerrainDimensions);
	~Terrain(void);

	void Draw(glm::mat4& mvp, glm::mat4& viewMat, glm::vec3& eyePos);
	glm::vec3 Sky(void);
	float GetYPosOfPlayer(float x, float z, float debug = 0.0f);
	glm::vec3& LP(void)
	{
		return m_lightPosition;
	}
private:
	void TerrainInit();
	void BufferAndShaderInit(void);
	void GenerateTerrainVerts(void);
	void GenerateTerrainIndices(void);
	void InitializeHeights(void);
	void GenerateColors(void);
private:
	void CompileShaders(void);
	void InitHeightmap(void);
	void GetUniformLocations(void);
	void SendUniformData(glm::mat4& proj, glm::mat4& view, glm::mat4& model, glm::vec3& eyePos);
	void InitBuffer(void);
	__forceinline glm::vec2 GetPositionOfPlayerOnTile(float x, float z)
	{
		float tx = x - floor(x);
		float tz = z - ceil(z);
		return glm::vec2(tx, tz);
	}
	__forceinline glm::vec2 GetSizeOfTile(float x, float z)
	{
		float tileWidth = floor(abs(x - (m_meshData.xHalf - m_dimensions.x)));
		float tileHeight = floor(abs(z - (m_meshData.zHalf - m_dimensions.z)));
		return glm::vec2(tileWidth, tileHeight);
	}
private:
	UniformLocations m_uniformLocations;
	Terrain::TerrainDimensions m_dimensions;
	Terrain::MeshData m_meshData;
	SHProgram m_shprogram;
	Buffer<VertexData> m_buffer;
	Heightmap m_hm;
	glm::vec3 m_lightPosition;
};

#endif