#include <windows.h>
#include <iostream>

int main(void)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int32_t k = 0; k < 255; ++k)
	{
		SetConsoleTextAttribute(h, k);
		std::cout << k << " hello world!" << std::endl;
	}
	std::cin.get();
}