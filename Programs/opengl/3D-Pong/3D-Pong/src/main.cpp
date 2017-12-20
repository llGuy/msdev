#include "misc.h"
#include "init.h"
#include "game\game.h"

#include <iostream>
#include <GLFW\glfw3.h>

int main(int argc, char* argv[])
{
	Window window(1200, 800, "3D-Pong");
	Init(&window);

	while (!window.WindowIsClosed())
	{
		window.Draw();
		window.Update();
	}
	window.DestroyWindow();
	
	return 0;
}