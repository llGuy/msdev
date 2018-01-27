#ifndef CHUNK_TEX_MAP_HEADER
#define CHUNK_TEX_MAP_HEADER

#include <vector>
#include <unordered_map>

#include "../block/block.h"

class CTextureMap
{
public:
	struct BData
	{
		Block* b;
		signed int elevation;
	};
	explicit CTextureMap(void)
	{
	}
public:
	void App(BData* bd)
	{
		m_map[Block::m_textureID[static_cast<unsigned int>(bd->b->BlockType())]].push_back(*bd);
		++m_numBlocks;
	}
	void Del(BData* bd)
	{
		std::vector<BData>& vec = m_map[Block::m_textureID[static_cast<unsigned int>(bd->b->BlockType())]];
		for (unsigned int i = 0; i < vec.size(); ++i)
		{
			if (vec[i].elevation == bd->elevation)
			{
				vec.erase(vec.begin() + i);
				--m_numBlocks;
				return;
			}
		}
	}
	void UpdateBuffer(void)
	{

	}
private:
	void CreateBuffer(void)
	{
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, );
	}
private:
	std::unordered_map<tex_id, std::vector<BData>> m_map;
	std::size_t m_numBlocks;
	std::size_t m_bufferSize;
	std::size_t m_bufferCapacity;
	GLuint m_vbo;
	GLuint m_ibo;
	GLuint m_vao;
};

#endif