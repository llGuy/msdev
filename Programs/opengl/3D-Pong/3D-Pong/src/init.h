#ifndef INIT_HEADER
#define INIT_HEADER

#include "misc.h"
#include "window\window.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

void GLFWInit(void)
{
	if (!glfwInit())
	{
		glfwTerminate();
		Log("failed to initialize GLFW");
	}
}
void GLEWInit(void)
{
	glewExperimental = true;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		glfwTerminate();
		Log(glewGetString(err));
	}
}
const bool WindowInitFailureCheck(Window* window)
{
	if (!window->FailedToCreateWindow())
	{
		window->DestroyWindow();
		glfwTerminate();

		return false;
	}
	return true;
}
void Init(Window* window)
{
	GLFWInit();
	window->Init();
	WindowInitFailureCheck(window);
	GLEWInit();
	window->AfterGLEWInit();
}

#endif