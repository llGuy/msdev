#include <iostream>
#include "window/window.h"
#include "engine/engine.h"

int main(int argc, char* argv[])
{
	std::cout << "started" << std::endl;
	Engine engine(0);
	std::cout << engine.BlockWPos(glm::vec3(-18.0f, 1.0f, 0.0f)).x << " " << engine.BlockWPos(glm::vec3(-18.0f, 1.0f, 0.0f)).y <<
		" " << engine.BlockWPos(glm::vec3(-18.0f, 1.0f, 0.0f)).z << std::endl;
	/*Window window(1700, 1100, "minecraft");

	while (window.WindowOpen())
	{
		window.Draw();
		window.Update();
	}
	*/
	std::cout << "finished" << std::endl;
	std::cin.get();
	return 0;
}