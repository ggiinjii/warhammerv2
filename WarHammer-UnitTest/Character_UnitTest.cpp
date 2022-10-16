#include "pch.h"
#include "CppUnitTest.h"
#include "Character/Character.h"
#include "Character/Horde/Orc.h"
#include "Character/Alliance/Knigth.h"
#include "Tool/Image.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CharacterUnitTest
{
	TEST_CLASS(Character_UnitTest)
	{
	public:

		TEST_METHOD(GetPvReturn60)
		{
            Image img;
			Orc* Thrall = new Orc("Thrall", 60, nullptr, nullptr, 5, "Stun", img);
			Assert::AreEqual(Thrall->GetPv().getPv(), 60);
            Assert::AreEqual(Thrall->GetPv().getPvMax(), 60);

            delete Thrall;
            Thrall = nullptr;
		}

		TEST_METHOD(SetPvSetPvTo100)
		{
            Image img;
			Orc* Thrall = new Orc("Thrall", 60, nullptr, nullptr, 5, "Stun", img);
			Thrall->SetPv(Pv (100,100));
			Assert::AreEqual(Thrall->GetPv().getPv(), 100);
            Assert::AreEqual(Thrall->GetPv().getPvMax(), 100);

            delete Thrall;
            Thrall = nullptr;
		}

		TEST_METHOD(GetCharacterStatusReturnNormal)
		{
            Image img;
			Orc* Thrall = new Orc("Thrall", 60, nullptr, nullptr, 5, "Stun", img);
			
			Assert::AreEqual((int)Thrall->getCharacterStatus(), (int)NORMAL);
            delete Thrall;
            Thrall = nullptr;
		}

		TEST_METHOD(setCharacterStatusToBurn)
		{
            Image img;
			Orc* Thrall = new Orc("Thrall", 60, nullptr, nullptr, 5, "Stun", img);
			Thrall->setCharacterStatus(BURN);
			Assert::AreEqual((int)Thrall->getCharacterStatus(), (int)BURN);
            delete Thrall;
            Thrall = nullptr;
		}

		TEST_METHOD(GetHitWithNoArmorReturn50)
		{
            Image img;
			Orc* Thrall = new Orc("Thrall", 60, nullptr, nullptr, 5, "Stun", img);
			Thrall->GetHit(10);
			Assert::AreEqual(Thrall->GetPv().getPv(), 50);
            Assert::AreEqual(Thrall->GetPv().getPvMax(), 60);
            delete Thrall;
            Thrall = nullptr;
		}

		TEST_METHOD(GetHitWithArmorReturn50)
		{
            Image img;
			Shield* shield = new Shield(20);

			Orc* Thrall = new Orc("Thrall", 60, nullptr, shield, 5, "Stun", img);
			Thrall->GetHit(10);
			Assert::AreEqual(Thrall->GetPv().getPv(), 60);

            delete Thrall;
            Thrall = nullptr;

            delete shield;
            shield = nullptr;
		}

		TEST_METHOD(IsCharacterStillAliveIsTrue)
		{
            Image img;
			Orc* Thrall = new Orc("Thrall", 60, nullptr, nullptr, 5, "Stun", img);
			Thrall->GetHit(10);
			Assert::IsTrue(Thrall->IsCharacterStillAlive());

            delete Thrall;
            Thrall = nullptr;
		}

		TEST_METHOD(IsCharacterStillAliveIsFalse)
		{
            Image img;
			Orc* Thrall = new Orc("Thrall", 60, nullptr, nullptr, 5, "Stun", img);
			Thrall->GetHit(60);
			Assert::IsFalse(Thrall->IsCharacterStillAlive());
			Thrall->GetHit(20);
			Assert::IsFalse(Thrall->IsCharacterStillAlive());
            delete Thrall;
            Thrall = nullptr;
		}

		TEST_METHOD(GetNameReturnThrall)
		{
            Image img;
			string orcName = "Thrall";
			Orc* Thrall = new Orc(orcName, 60, nullptr, nullptr, 5, "Stun", img);
			Assert::AreEqual(Thrall->GetName(), orcName);

            delete Thrall;
            Thrall = nullptr;
		}

		TEST_METHOD(AttackReturnS_OK)
		{
            Image img;
			Knigth* Billy = new Knigth("Billy", 20, nullptr, nullptr, 3, "Charge", img);

			Sword* orcSword = new Sword(10);
			Orc* Thrall = new Orc("Thrall", 60, orcSword, nullptr, 5, "Stun", img);

			HRESULT result= Thrall->Attack(Billy);

			Assert::AreEqual(result, S_OK);
			Assert::AreEqual(Billy->GetPv().getPv(), 10);
            

			Thrall->SetWeapon(nullptr);
			result=Thrall->Attack(Billy);

			Assert::AreEqual(result, S_OK);
			Assert::AreEqual(Billy->GetPv().getPv(), 9);
            Assert::AreEqual(Billy->GetPv().getPvMax(), 20);

            delete Thrall;
            Thrall = nullptr;
            delete Billy;
            Billy = nullptr;
		}

		TEST_METHOD(AttackReturnS_FALSE)
		{
            Image img;
			Knigth* Billy = new Knigth("Billy", 20, nullptr, nullptr, 3, "Charge", img);

			Sword* orcSword = new Sword(10);
			Orc* Thrall = new Orc("Thrall", 60, orcSword, nullptr, 5, "Stun", img);

			Thrall->setCharacterStatus(STUN);
			HRESULT result = Thrall->Attack(Billy);

			Assert::AreEqual(result, S_FALSE);
			Assert::AreEqual(Billy->GetPv().getPv(), 20);
            delete Billy;
            Billy = nullptr;
            delete Thrall;
            Thrall = nullptr;
		}
		TEST_METHOD(AttackReturnE_Fail)
		{
            Image img;
			Knigth* Billy = new Knigth("Billy", 20, nullptr, nullptr, 3, "Charge", img);

			Sword* orcSword = new Sword(10);
			Orc* Thrall = new Orc("Thrall", 60, orcSword, nullptr, 5, "Stun", img);


			HRESULT result = Thrall->Attack(nullptr);
			Assert::AreEqual(result, E_FAIL);
			Assert::AreEqual(Billy->GetPv().getPv(), 20);
            delete Billy;
            Billy = nullptr;
            delete orcSword;
            orcSword = nullptr;
            delete Thrall;
            Thrall = nullptr;
		}

		TEST_METHOD(SpecialCapacityCheckReturnE_Fail)
		{
            Image img;
			string orcName = "Thrall";
			Orc* Thrall = new Orc(orcName, 60, nullptr, nullptr, 5, "Stun", img);

			Assert::AreEqual(Thrall->SpecialCapacityCheck(nullptr), E_FAIL);
            delete Thrall;
            Thrall = nullptr;
		}
		TEST_METHOD(SpecialCapacityCheckReturnS_False)
		{
            Image img;
			string orcName = "Thrall";
			Orc* Thrall = new Orc(orcName, 60, nullptr, nullptr, 5, "Stun", img);

			Knigth* Billy = new Knigth("Billy", 20, nullptr, nullptr, 3, "Charge", img);

			Thrall->SetCurrentCd(3);
			Assert::AreEqual(Thrall->SpecialCapacityCheck(Billy), S_FALSE);

			Thrall->setCharacterStatus(STUN);
			Thrall->SetCurrentCd(0);
			Assert::AreEqual(Thrall->SpecialCapacityCheck(Billy), S_FALSE);
            delete Thrall;
            Thrall = nullptr;
            delete Billy;
            Billy = nullptr;
		}

		TEST_METHOD(SpecialCapacityCheckReturnS_OK)
		{
            Image img;
			string orcName = "Thrall";
			Orc* Thrall = new Orc(orcName, 60, nullptr, nullptr, 5, "Stun", img);

			Knigth* Billy = new Knigth("Billy", 20, nullptr, nullptr, 3, "Charge", img);

			Thrall->SetCurrentCd(0);
			Assert::AreEqual(Thrall->SpecialCapacityCheck(Billy), S_OK);
            delete Thrall;
            Thrall = nullptr;
            delete Billy;
            Billy = nullptr;
		}

	};
}
