#include <iostream>

#include "window\window.h"

void Greeting(void);

int main(int argc, char* argv[])
{
	Greeting();

	Window window(3100, 1900, "snake");
	while (window.WindowIsOpen())
	{
		window.Draw();
		window.Update();
	}

	return 0;
}