#include "pch.h"
#include "CppUnitTest.h"
#include "Tool/Pv.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PvUnitTest
{
	TEST_CLASS(Pv_UnitTest)
	{
	public:
		TEST_METHOD(Is60pvMinus15Equals45)
		{
			Pv pvTest (60,60);
			
			pvTest=pvTest-15;

			Assert::AreEqual(pvTest.getPv(), 45);
			Assert::AreEqual(pvTest.getPvMax(), 60);
		}
			
	};
}
