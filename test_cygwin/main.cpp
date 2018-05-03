#define GLM_EXPERIMENTAL
#define GLEW_STATIC

#include <iostream>
#include <vector>
#include <type_traits>
#include <iterator>
#include <algorithm>
#include "glew.h"
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

const char* NEW_LINE = "\n";

uint32_t CreateTriangle(void)
{
  struct Vertex
  {
    glm::vec2 position;
    glm::vec3 color;
  };

  Vertex vertices[3];
  
  uint32_t bufferID;
  glGenBuffers(1, &bufferID);
  glBindBuffer(GL_ARRAY_BUFFER, bufferID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  return bufferID;
}

int main(void)
{
  if(!glfwInit())
    {
      std::cerr << "failed to initialize GLFW\n";
    }
  GLFWwindow* window;
  window = glfwCreateWindow(1200, 800, "cygwin test", 0, 0);
  if(!window)
    {
      std::cerr << "failed to initialize window\n";
    }
  
  glfwMakeContextCurrent(window);
  
  while(!glfwWindowShouldClose(window))
    {
      glClear(GL_COLOR_BUFFER_BIT);
      glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

      glfwSwapBuffers(window);
      glfwPollEvents();
    }

  glfwDestroyWindow(window);
  glfwTerminate();
  
  return 0;
}
