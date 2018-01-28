#include "stdafx.h"
#include "CppUnitTest.h"
#include "../minecraft/src/engine/chunk/chunk.h"
#include "../minecraft/src/engine/engine.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
			Engine engine(0);
			float x = engine.BlockWPos(glm::vec3(-18.0f, 1.0f, 0.0f)).x;
			float y = engine.BlockWPos(glm::vec3(-18.0f, 1.0f, 0.0f)).y;
			float z = engine.BlockWPos(glm::vec3(-18.0f, 1.0f, 0.0f)).z;

			Assert::IsTrue(fabs(x + 18.0) < 1e-7);


		}

	};
}