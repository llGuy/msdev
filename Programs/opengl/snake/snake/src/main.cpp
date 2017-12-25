#include <iostream>

#include "window\window.h"
#include "log.h"

int main(int argc, char* argv[])
{
	Log("Welcome to Snake in 3D!!!");

	Window window(1800, 1200, "snake");
	while (window.WindowIsOpen())
	{
		window.Draw();
		window.Update();
	}

	return 0;
}