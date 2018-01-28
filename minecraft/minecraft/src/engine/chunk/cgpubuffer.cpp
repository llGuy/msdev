#include "cgpubuffer.h"

namespace gpu
{
	/* class CGPUVAO: */
	void CGPUVAO::Init(void)
	{
		glGenVertexArrays(1, &m_vaoID);
		glBindVertexArray(m_vaoID);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, sizeof(float) * 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3 + sizeof(unsigned int), 0);
		glVertexAttribDivisor(0, 1);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, sizeof(unsigned int), GL_UNSIGNED_INT, GL_FALSE, 
			sizeof(float) * 3 + sizeof(unsigned int), (void*)(sizeof(float) * 3));
		glVertexAttribDivisor(1, 1);
	}
	void CGPUVAO::Bind(void) const
	{
		glBindVertexArray(m_vaoID);
	}

	/* class CGPUBuffer: */

	void CGPUBuffer::Init(::std::size_t components, BData* bd)
	{
		m_vao = new CGPUVAO();
		BufferInit(components, bd);
		m_vao->Init();
		UnBind();
	}

	void CGPUBuffer::BufferInit(::std::size_t components, BData* bd)
	{
		glGenBuffers(1, &m_bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		glBufferData(GL_ARRAY_BUFFER, components * sizeof(*bd), bd, GL_DYNAMIC_DRAW);
	}

	void CGPUBuffer::UnBind(void) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	VAO* CGPUBuffer::Vao(void)
	{
		return m_vao;
	}
}