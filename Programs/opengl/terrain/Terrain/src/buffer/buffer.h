#ifndef BUFFER_HEADER
#define BUFFER_HEADER

class Buffer
{
public:
	explicit Buffer(void* vd, void* id, unsigned int numV, unsigned int numI);
	void Init(void);
	void BindElement(void);
	void BindArray(void);
	void BindVertexArray(void);
private:
	unsigned int VertexDataSize(void) const;
	unsigned int IndexDataSize(void) const;
	void InitializeGLBuffer(void);
	void SendVertexData(void);
	void SendIndexData(void);
private:
	void* m_vertices;			// vertex data
	void* m_indices;		    // index data

	unsigned int m_numV;	// number of vertices
	unsigned int m_numI;	// number of indices

	unsigned int m_bufferID;
	unsigned int m_vaoID;
};

#endif