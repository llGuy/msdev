#include "cgpubuffer.h"
#include "../gpublockdata.h"

namespace minecraft
{
	namespace chunk
	{
		namespace gpu
		{
			/* class CGPUVAO: */
			void CGPUVAO::Init(void* bd)
			{
				BData* bdata = static_cast<BData*>(bd);
				glGenVertexArrays(1, &m_vaoID);
				glBindVertexArray(m_vaoID);

				glEnableVertexAttribArray(0);
				glEnableVertexAttribArray(1);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(*bdata), 0);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(*bdata), (void*)(sizeof(float) * 3));

				glVertexAttribDivisor(0, 1);
				glVertexAttribDivisor(1, 1);
			}
			void CGPUVAO::Bind(void) const
			{
				glBindVertexArray(m_vaoID);
			}

			void CGPUVAO::UnBind(void) const
			{
				glBindVertexArray(0);
			}

			/* class CGPUBuffer: */

			void CGPUBuffer::Load(::std::size_t components, BData* bd)
			{
				m_vao = new CGPUVAO();
				LoadBuffer(components, bd);
				m_vao->Init(bd);
				UnBind();
			}

			void CGPUBuffer::LoadBuffer(::std::size_t components, BData* bd)
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
	}
}