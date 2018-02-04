#ifndef CGPU_BUFFER_HEADER
#define CGPU_BUFFER_HEADER

#include <iostream>

#include "../gpublockdata.h"
#include "../../../buffer/vao.h"

namespace chunk
{
	namespace gpu
	{
		class CGPUVAO
			: public VAO
		{
		public:
			explicit CGPUVAO(void) = default;
			void Init(void* bd) override;
			void Bind(void) const override;
			void UnBind(void) const override;
		};

		class CGPUBuffer
		{
		public:
			explicit CGPUBuffer(void) = default;
			void Load(std::size_t components, BData* data);
			VAO* Vao(void);
		private:
			void LoadBuffer(std::size_t components, BData* data);
			void UnBind(void) const;
		private:
			unsigned int m_bufferID;
			VAO* m_vao;
		};
	}
}

#endif