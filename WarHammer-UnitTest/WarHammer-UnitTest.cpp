#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WarHammerUnitTest
{
	TEST_CLASS(WarHammerUnitTest)
	{
	public:
		
		TEST_METHOD(isSwordDeadDamageOk)
		{
			Sword SwordTest(20);
			Assert::AreEqual(SwordTest.DealDamage(), 20);
		}
	};
}
