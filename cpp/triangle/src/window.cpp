#include "window.h"
#include "init.h"

Window::Window(int32_t width, int32_t height, const char* title)
  : m_width(width), m_height(height)
{
  Init(title);
}

void Window::Render(void)
{
  // doesn't draw anything
}

void Window::Update(void)
{
  glfwSwapBuffers(m_glfwWindow);
  glfwPollEvents();
}

void Window::Init(const char* title)
{
  GLFWInit();
  WindowInit(title);
}

const bool Window::Open(void)
{
  return !glfwWindowShouldClose(m_glfwWindow);
}

void Window::DestroyWindow(void)
{
  glfwDestroyWindow(m_glfwWindow);
  glfwTerminate();
}

void Window::WindowInit(const char* title)
{
  m_glfwWindow = glfwCreateWindow(m_width, m_height, title, 0, 0);
  if(!m_glfwWindow)
  {
    std::cerr << "failed to initialize window" << std::endl;
  }
}
