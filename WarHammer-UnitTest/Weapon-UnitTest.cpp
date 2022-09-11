#include "pch.h"
#include "CppUnitTest.h"
#include "Inventory/Weapon/SubWeapon/Sword.h"
#include "Inventory/Weapon/SubWeapon/Hammer.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WeaponUnitTest
{
	TEST_CLASS(Weapon_UnitTest)
	{
	public:
		
		TEST_METHOD(SwordDealDamageEqual20)
		{
			Sword SwordTest(20);
			Assert::AreEqual(SwordTest.DealDamage(), 20);
		}

		TEST_METHOD(HammerDealDamageEqual20)
		{
			Hammer HammerTest(20);
			HammerTest.setDamage(40);
			Assert::AreEqual(HammerTest.DealDamage(), 40);
		}
	};
}
