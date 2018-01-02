#include <GL/glew.h>

#include "buffer.h"
#include "../primitives/vertex.h"

Buffer::Buffer(void* vd, void* id, unsigned int numV, unsigned int numI)
	: m_vertices(vd), m_indices(id), m_numV(numV), m_numI(numI)
{
}
void Buffer::Init(void)
{
	InitializeGLBuffer();
	SendVertexData();
	SendIndexData();
}
void Buffer::BindElement(void)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
}
void Buffer::BindArray(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
}
void Buffer::BindVertexArray(void)
{
	// bind vertex array
}
unsigned int Buffer::VertexDataSize(void) const
{
	return sizeof(Vertex) * m_numV;
}
unsigned int Buffer::IndexDataSize(void) const
{
	return sizeof(unsigned short) * m_numI;
}
void Buffer::InitializeGLBuffer(void)
{
	glGenBuffers(1, &m_bufferID);
	BindArray();
	BindElement();
	glBufferData(GL_ARRAY_BUFFER, VertexDataSize() + IndexDataSize(), 0, GL_STATIC_DRAW);
}
void Buffer::SendVertexData(void)
{
	glBufferSubData(GL_ARRAY_BUFFER, 0, VertexDataSize(), m_vertices);
}
void Buffer::SendIndexData(void)
{
	glBufferSubData(GL_ARRAY_BUFFER, VertexDataSize(), IndexDataSize(), m_indices);
}