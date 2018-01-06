#include <iostream>
#include "window/window.h"
#include <GL/glew.h>
#include <chrono>

int main(int argc, char* argv[])
{
	
	Window window(3800, 2500, "terrain");
	while (window.WindowOpen())
	{
		window.Draw();
		window.Update();
	}
	
	return 0;
}