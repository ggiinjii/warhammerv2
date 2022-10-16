#include "pch.h"
#include "CppUnitTest.h"
#include "Character/Alliance/Knigth.h"
#include "Character/Horde/Orc.h"
#include "Tool/Image.h"
#include <winerror.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace KnightUnitTest
{
	TEST_CLASS(Knight_UnitTest)
	{
	public:

		TEST_METHOD(KnigthSpecialCapacityReturnE_FAIL)
		{
            Image img;

			Knigth Anduin("Anduin", 20,nullptr,nullptr,10,"Pour l'alliance", img);

			Assert::AreEqual(Anduin.SpecialCapacity(nullptr).getResult(), E_FAIL);
		}

		TEST_METHOD(KnightSpecialCapacityNotReturnE_FAIL)
		{
            Image img;
			Sword* LunarSword = new Sword(5);
			Knigth Anduin("Anduin", 20, LunarSword, nullptr, 10, "Pour l'alliance", img);

			Orc* Thrall = new Orc("Thrall", 60, nullptr, nullptr, 5, "Stun", img);

			HRESULT result = Anduin.SpecialCapacity(Thrall).getResult();

			if (result==S_OK)
				Assert::AreEqual(Thrall->GetPv().getPv(), 50);
			else if (result==S_FALSE)
				Assert::AreEqual(Thrall->GetPv().getPv(),60 );

            Assert::AreEqual(Thrall->GetPv().getPvMax(), 60);
            delete LunarSword;
            LunarSword = nullptr;
            delete Thrall;
            Thrall = nullptr;
		}
	};
}
