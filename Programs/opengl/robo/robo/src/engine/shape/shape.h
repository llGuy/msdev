#ifndef SHAPE_HEADER
#define SHAPE_HEADER

#include <glm/glm.hpp>

#include "../data/vertex_data.h"
#include "../data/index_data.h"
#include "../../buffer/buffer.h"

struct UniformLocations;
struct Time;

class Shape
{
public:
	virtual void Draw(glm::mat4& proj, glm::mat4& view, glm::mat4& model,
		glm::vec3& eyePos, glm::vec3& lightPos, UniformLocations* locations,
		Time* timeData) = 0;
	virtual void Init(void) = 0;
protected:
	virtual void VerticesInit(void) = 0;
	virtual void IndicesInit(void) = 0;
	virtual void BufferInit(void) = 0;
	virtual void DeleteRAM(void) = 0;

	virtual void UniformData(glm::mat4& proj, glm::mat4& view, glm::mat4& model,
		glm::vec3& eyePos, glm::vec3& lightPos,
		Time* timeData, UniformLocations* locations) = 0;
protected:
	VertexData m_vd;
	IndexData m_id;
	Buffer m_buffer;
};

#endif