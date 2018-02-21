#include <iostream>

#define HACK -0xffff

class CHack
{
public:
	CHack(void)
		: m_i(0)
	{
	}
	void Hack(void)
	{
		m_array[-1] = HACK;
	}
	const int32_t I(void)
	{
		return m_i;
	}
private:
	const int32_t m_i;
	int32_t m_array[2];
};

int main(void)
{
	CHack ch;
	std::cout << std::hex << ch.I() << std::endl;
	ch.Hack();
	std::cout << std::hex << ch.I() << std::endl;

	std::cin.get();
}