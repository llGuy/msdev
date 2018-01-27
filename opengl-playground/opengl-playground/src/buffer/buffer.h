#ifndef BUFFER_HEADER
#define BUFFER_HEADER

#include "../data/vertex_data.h"
#include "../data/index_data.h"

template<typename _Dt = VertexData>
class Buffer
{
public:
	explicit Buffer(void)
	{
	}
	explicit Buffer(_Dt vData, IndexData iData)
		: m_vData(vData), m_iData(iData)
	{
	}
	void Init(_Dt vData, IndexData iData, bool textured = false)
	{
		m_vData = vData;
		m_iData = iData;

		SendVertexData();
		SendIndexData();
		CreateVertexArray(textured);
	}
	void Init(bool textured = false)
	{
		SendVertexData();
		SendIndexData();
		CreateVertexArray(textured);
	}
	void BindElement(void)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	}
	void BindArray(void)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	}
	void BindVertexArray(void)
	{
		glBindVertexArray(m_vaoID);
	}
	void BindAll(void)
	{
		BindVertexArray();
		BindArray();
		BindElement();
	}
	unsigned int NumIndices(void) const
	{
		return m_iData.numIndices;
	}
	unsigned int NumVertices(void) const
	{
		return m_vData.numVertices;
	}
private:
	unsigned int VertexDataSize(void) const
	{
		return sizeof(*m_vData.vData) * m_vData.numVertices;
	}
	unsigned int IndexDataSize(void) const
	{
		return sizeof(unsigned short) * m_iData.numIndices;
	}
	void SendVertexData(void)
	{
		glGenBuffers(1, &m_vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, VertexDataSize(), m_vData.vData, GL_STATIC_DRAW);
	}
	void SendIndexData(void)
	{
		glGenBuffers(1, &m_indexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexDataSize(), m_iData.iData, GL_STATIC_DRAW);
	}
	void CreateVertexArray(bool textured = false)
	{
		glGenVertexArrays(1, &m_vaoID);
		glBindVertexArray(m_vaoID);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		if (textured)
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		}
		else
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		}
	}
private:
	_Dt m_vData;
	IndexData m_iData;

	unsigned int m_vertexBufferID;
	unsigned int m_indexBufferID;
	unsigned int m_vaoID;
};

#endif