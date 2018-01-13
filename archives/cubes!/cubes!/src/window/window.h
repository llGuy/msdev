#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include <glm/glm.hpp>

class GLFWwindow;
class Camera;
class Cubes;

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
	void Init(void);
	void GLFWInit(void);
	void GLEWInit(void);
	void AfterGLEWInit(void);
	void PollEvent(void);
	void PollCameraMovement(void);
	void PollMouseMovement(void);
private:
	unsigned int m_width;
	unsigned int m_height;
	const char* m_title;
	
	GLFWwindow* m_glfwWindow;
	glm::mat4 m_perspectiveMatrix;
	glm::mat4 m_cameraMatrix;

	Cubes* m_cubes;
	Camera* m_camera;
};

#endif