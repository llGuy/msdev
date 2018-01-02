#include <iostream>

#include "window/window.h"

int main(int argc, char* argv)
{
	Window window(3800, 2500, "cubes!");

	while (window.WindowOpen())
	{
		window.Draw();
		window.Update();
	}

	return 0;
}