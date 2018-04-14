#ifndef TEST_HEADER
#define TEST_HEADER

#include <iostream>
#include <functional>

namespace glmath
{
	class Test
	{
	public:
		explicit Test(std::function<bool(float)> func, float expected, const char* msg)
			: m_func(func), m_expected(expected), m_msg(msg)
		{
		}

		void RunTest(void)
		{
			if (m_func(m_expected)) std::cout << m_msg << " : " << "SUCCESS" << std::endl;
			else std::cout << m_msg << " : " << "FAILURE" << std::endl;
		}
	private:
		std::function<bool(float)> m_func;
		const char* m_msg;
		float m_expected;
	};
}

#endif