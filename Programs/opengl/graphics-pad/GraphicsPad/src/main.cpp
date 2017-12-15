#define GL_STATIC

#include <iostream>
#include "glfwwindow.h"

int main(int argc, char* argv[])
{
	Window window(1200, 400, "Graphics Pad");
	while(window.IsWindowOpen())
	{
		window.Draw();
		window.Update();
	}

	//std::cin.get();

	return 0;
}