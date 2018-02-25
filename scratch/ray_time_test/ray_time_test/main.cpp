#include <iostream>
#include <chrono>

int main(void)
{
	std::chrono::high_resolution_clock::time_point tp = std::chrono::high_resolution_clock::now();
	for (float x = 0.0f; x <= 6.0f; x += 6.0f * 0.05f)
	{
		std::cout << ' ' << std::endl;
	}
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::duration d = end - tp;
	std::cout << d.count() / 1000000 << std::endl;
	std::cin.get();
}