#include "stdafx.h"
#include "CppUnitTest.h"
#include "../glmath/src/math/vmath.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_test
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			glmath::Vector3f base1(1.0f, 0.0f, 0.0f);
			glmath::Vector3f base2(0.0f, 1.0f, 0.0f);
			glmath::Vector3f base3 = glmath::Cross(base1, base2);

			float perp = glmath::Dot(base3, base1);
			
			Assert::AreEqual(0.0f, perp, 0.00001f, L"CROSS PRODUCT & DOT PRODUCT : SUCCESS");
		}

	};
}