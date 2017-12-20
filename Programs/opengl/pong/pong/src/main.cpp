#include "window\window.h"

int main(int argc, char* argv[])
{
	Window window(1800, 1500, "pong");

	while (window.WindowIsOpen())
	{
		window.Draw();
		window.Update();
	}

	return 0;
}