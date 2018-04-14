#include <GLFW/glfw3.h>
#include <stdint.h>
#include <iostream>

class Window
{
public:
  Window(int32_t width, int32_t height, const char* title);
  ~Window(void) = default;

  void Render(void);
  void Update(void);
  
  void Init(const char* title);
  const bool Open(void);
  void DestroyWindow(void);
private:
  void WindowInit(const char* title);
private:
  int32_t m_width;
  int32_t m_height;
  GLFWwindow* m_glfwWindow;
};
