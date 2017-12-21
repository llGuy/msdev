#ifndef WINDOW_HEADER
#define WINDOW_HEADER

class GLFWwindow;
class Game;

class Window
{
public:
	explicit Window(unsigned int width, 
		unsigned int height, 
		const char* title);
	~Window(void);
public:
	void Draw(void);
	void Update(void);
	const bool WindowIsOpen(void);
private:
	void Init(void);
	void InitAfterGLEWInit(void);
	void PollKeys(void);
	void PollPaddleLeftMovement(void);
	void PollPaddleRightMovement(void);
private:
	unsigned int m_width;
	unsigned int m_height;
	const char* m_title;

	GLFWwindow* m_glfwWindow;
	Game* m_game;
};

#endif