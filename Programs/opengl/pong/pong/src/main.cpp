#include "window\window.h"

#include <iostream>

int main(int argc, char* argv[])
{
	Window window(2000, 1500, "pong");

	while (window.WindowIsOpen())
	{
		window.Draw();
		window.Update();
	}

	return 0;
}