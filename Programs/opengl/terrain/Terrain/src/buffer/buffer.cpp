#include <GL/glew.h>

#include "buffer.h"
#include "../primitives/vertex.h"

Buffer::Buffer(void* vd, void* id, unsigned int numV, unsigned int numI)
	: m_vertices(vd), m_indices(id), m_numV(numV), m_numI(numI)
{
}
void Buffer::Init(void)
{
	SendVertexData();
	SendIndexData();
	CreateVertexArray();
}
void Buffer::BindElement(void)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
}
void Buffer::BindArray(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
}
void Buffer::BindVertexArray(void)
{
	glBindVertexArray(m_vaoID);
}
void Buffer::BindAll(void)
{
	BindArray();
	BindElement();
	BindVertexArray();
}
unsigned int Buffer::NumIndices(void) const
{
	return m_numI;
}
unsigned int Buffer::NumVertices(void) const
{
	return m_numV;
}
unsigned int Buffer::VertexDataSize(void) const
{
	return sizeof(Vertex) * m_numV;
}
unsigned int Buffer::IndexDataSize(void) const
{
	return sizeof(unsigned short) * m_numI;
}
void Buffer::SendVertexData(void)
{
	glGenBuffers(1, &m_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, VertexDataSize(), m_vertices, GL_STATIC_DRAW);
}
void Buffer::SendIndexData(void)
{
	glGenBuffers(1, &m_indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexDataSize(), m_indices, GL_STATIC_DRAW);
}
void Buffer::CreateVertexArray(void)
{
	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}
