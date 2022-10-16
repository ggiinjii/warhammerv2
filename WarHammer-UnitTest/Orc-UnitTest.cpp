#include "pch.h"
#include "CppUnitTest.h"
#include "Character/Horde/Orc.h"
#include "Inventory/Weapon/SubWeapon/Hammer.h"
#include "Character/Alliance/Knigth.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OrcUnitTest
{
	TEST_CLASS(Orc_UnitTest)
	{
	public:

		TEST_METHOD(isGetHitNoArmordeal20Pv)
		{
            Image img;
			Hammer* DoomHammer = new Hammer(8);
			Orc* Thrall = new Orc("Thrall", 60, DoomHammer, nullptr, 5, "Stun", img);
			Thrall->GetHit(20);

			Assert::AreEqual(Thrall->GetPv().getPv(), 40);
            delete DoomHammer;
            DoomHammer = nullptr;
            delete Thrall;
            Thrall = nullptr;
		}

		TEST_METHOD(isGetHitWithArmorDeal0Pv)
		{
            Image img;
			Hammer* DoomHammer = new Hammer(8);
			Shield* shield = new Shield(10);
			Orc* Thrall = new Orc("Thrall", 60, DoomHammer, shield, 5, "Stun", img);
			Thrall->GetHit(20);

			Assert::AreEqual(Thrall->GetPv().getPv(), 60);
            delete DoomHammer;
            DoomHammer = nullptr;
            delete Thrall;
            Thrall = nullptr;
            delete shield;
            shield = nullptr;
		}



		TEST_METHOD(OrcSpecialCapacityReturnE_FAIL)
		{
            Image img;
			Orc Thrall ("Thrall", 60, nullptr, nullptr, 5, "Stun", img);

			Assert::AreEqual(Thrall.SpecialCapacity(nullptr).getResult(), E_FAIL);
		}

		TEST_METHOD(OrcSpecialCapacityNotReturnE_FAIL)
		{
            Image img;
			Orc Thrall ("Thrall", 60, nullptr, nullptr, 5, "Stun", img);
			Knigth* Anduin = new Knigth("Anduin", 20, nullptr, nullptr, 10, "Pour l'alliance", img);

			HRESULT result = Thrall.SpecialCapacity(Anduin).getResult();

			CONDITION stun = STUN;
			CONDITION Normal = NORMAL;

			if (result == S_OK)
				Assert::AreEqual((int)Anduin->getCharacterStatus(), (int)stun);
			else if (result == S_FALSE)
				Assert::AreEqual((int)Anduin->getCharacterStatus(), (int)Normal);
            delete Anduin;
            Anduin = nullptr;
		}

	};
}
