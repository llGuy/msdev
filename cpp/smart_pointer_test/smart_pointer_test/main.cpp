#include <array>
#include <memory>
#include <iostream>

class Base
{
public:
	virtual void Print(void)
	{
		std::cout << "base" << std::endl;
	}
	int b;
};

class Derived
	: public Base
{
public:
	void Print(void) override
	{
		std::cout << "derived" << std::endl;
	}
	int d;
};

int main()
{
	std::unique_ptr<Base> ptr0 = std::make_unique<Base>();
	std::unique_ptr<Base> ptr1 = std::make_unique<Derived>();
	ptr0->Print();
	ptr1->Print();

	std::unique_ptr<int[]> arr = std::make_unique<int[]>(5);
	for (int32_t i = 0; i < 5; ++i) arr[i] = i;
	for (int32_t i = 0; i < 5; ++i) std::cout << arr[i] << std::endl;

	std::cin.get();
}