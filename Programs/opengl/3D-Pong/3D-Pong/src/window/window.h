#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include "..\game\game.h"
class GLFWwindow;

class Window
{
public:
	explicit Window(unsigned int width, unsigned int height, const char* title);
	~Window(void);
public:
	void Draw(void);
	void Update(void);
	void Init(void);
	void AfterGLEWInit(void);
	const bool FailedToCreateWindow(void);
	const bool WindowIsClosed(void);
	void DestroyWindow(void);

	const unsigned int Width(void);
	const unsigned int Height(void);
	const char*		   Title(void);
private:
	unsigned int m_width;
	unsigned int m_height;
	const char* m_title;

	GLFWwindow* m_glfwWindow;
	Game m_game;
};

#endif