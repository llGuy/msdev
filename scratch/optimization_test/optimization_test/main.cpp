#include <iostream>
#include <chrono>

void NoOp(void)
{
	std::chrono::high_resolution_clock::time_point n = std::chrono::high_resolution_clock::now();
	for (uint32_t i = 0; i < 100; ++i)
	{
		uint32_t j = i * 3;
		uint32_t k = (i + 1) * 3;
		//std::cout << j << " " << k << std::endl;
	}
	std::chrono::high_resolution_clock::time_point p = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::duration d = p - n;
	std::cout << d.count() << std::endl;
	std::cin.get();
}

void Op(void)
{
	std::chrono::high_resolution_clock::time_point n = std::chrono::high_resolution_clock::now();
	for (uint32_t i = 0; i < 100; ++i)
	{
		uint32_t a = (i) + ((i + 1) << 16);
		a *= 3;
		uint32_t j = a >> 16;
		uint32_t k = a & 0b00000000000000001111111111111111;
		//std::cout << j << " " << k << std::endl;
	}
	std::chrono::high_resolution_clock::time_point p = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::duration d = p - n;
	std::cout << d.count() << std::endl;
	std::cin.get();
}

int main(void)
{
	NoOp();
	Op();
}