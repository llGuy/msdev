#include <GLFW/glfw3.h>

void GLFWInit(void)
{
  if(!glfwInit())
  {
    std::cerr << "glfw init failed" << std::endl;
  }
}
