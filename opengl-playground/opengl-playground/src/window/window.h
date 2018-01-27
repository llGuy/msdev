#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include <glm/glm.hpp>

class BlockHandler;
class Camera;
class FPSPlayer;
class Terrain;
class Water;
class GLFWwindow;

class Window
{
public:
	explicit Window(unsigned int width, unsigned int height, const char* title);
	~Window(void);
public:
	void Draw(void);
	void Update(void);
	const bool WindowOpen(void);
	bool& CameraPlayerView(void);
private:
	void PollKeys(void);
	void PollCameraMovement(void);
	void PollMouseMovement(void);
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
	Terrain* m_terrain;
	Camera* m_camera;
	BlockHandler* m_bh;
	FPSPlayer* m_player;
	Water* m_water;
	glm::mat4 m_projMat;
	glm::mat4 m_view;

	bool m_cameraPlayerView;
};

#endif