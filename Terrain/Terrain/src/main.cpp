#include <iostream>

#include "window/window.h"
#include "terrain/terrain.h"

int main(int argc, char* argv[])
{
	Window window(1500, 1200, "terrain");
	while (window.WindowOpen())
	{
		window.Draw();
		window.Update();
	}

	return 0;
}