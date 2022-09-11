#include "pch.h"
#include "CppUnitTest.h"
#include "Inventory/Armor/SubArmor/Shield.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ArmorUnitTest
{
	TEST_CLASS(Armor_UnitTest)
	{
	public:

		TEST_METHOD(getPvBonusReturn20)
		{
			Shield Rondache(20);
			Assert::AreEqual(Rondache.getPvBonus(), 20);
			Rondache.setPvBonus(60);
			Assert::AreEqual(Rondache.getPvBonus(), 60);
		}

		TEST_METHOD(setPvBonusSetPvBonusTo60)
		{
			Shield Rondache(20);
			Rondache.setPvBonus(60);
			Assert::AreEqual(Rondache.getPvBonus(), 60);
		}

		TEST_METHOD(getDamagedReturn60)
		{
			Shield Rondache(100);
			Rondache.getDamaged(40);
			Assert::AreEqual(Rondache.getPvBonus(), 60);
		}

		TEST_METHOD(getArmorStatusReturnAllStatus)
		{
			Shield Rondache(100);
			ARMORSTATUS status = PERFECT;

			Rondache.getDamaged(9);
			Assert::AreEqual((int)Rondache.getArmorStatus(), (int)status);

			status = SCRATCHED;
			Rondache.getDamaged(40);
			Assert::AreEqual((int)Rondache.getArmorStatus(), (int)status);

			status = BROKEN;
			Rondache.getDamaged(29);
			Assert::AreEqual((int)Rondache.getArmorStatus(), (int)status);

			status = DEAD;
			Rondache.getDamaged(20);
			Assert::AreEqual((int)Rondache.getArmorStatus(), (int)status);

		}

		

			
	};
}