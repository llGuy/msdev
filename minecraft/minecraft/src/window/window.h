#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include <glm/glm.hpp>

struct GLFWwindow;

class Window
{
public:
	explicit Window(unsigned int width, unsigned int height, const char* title);
	~Window(void);
public:
	void Draw(void);
	void Update(void);
	const bool WindowOpen(void);
private:
	void WindowInit(void);
	void GLFWInit(void);
	void GLEWInit(void);
	void AfterGLEWInit(void);	
private:
	unsigned int m_width;
	unsigned int m_height;
	const char* m_title;
	GLFWwindow* m_glfwWindow;
	glm::mat4 m_projectionMatrix;
};

#endif