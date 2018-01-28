#ifndef VAO_HEADER
#define VAO_HEADER

#include "../chunk/gpublockdata.h"

class VAO
{
public:
	virtual void Init(void) = 0;
	virtual void Bind(void) const = 0;
protected:
	unsigned int m_vaoID;
};

#endif