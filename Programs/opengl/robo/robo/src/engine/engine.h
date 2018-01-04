#ifndef ENGINE_HEADER
#define ENGINE_HEADER

#include "engine_comon.h"

class RoboEngine
{
public:
	explicit RoboEngine(void);
	~RoboEngine(void);
	
	void Draw(void);
private:
	void InitShaders(void) const;
private:
	Terrain m_terrain;
	SHProgram m_shaders;
};

#endif