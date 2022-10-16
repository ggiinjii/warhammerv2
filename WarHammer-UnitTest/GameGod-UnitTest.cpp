#include "pch.h"
#include "CppUnitTest.h"
#include "GameObject/GameGod.h"
#include "Character/Horde/Orc.h"
#include "Character/Alliance/Knigth.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameGodUnitTest
{
	TEST_CLASS(GameGod_UnitTest)
	{
	public:

		TEST_METHOD(LauchSpecialCapacityReturnS_OK)
		{
            Image img;
			GameGod Kimimaro;

			Sword* MasterSword = new Sword(10);

			Knigth* Billy = new Knigth("Billy", 0, MasterSword, nullptr, 3, "Charge", img);
			Orc* Thrall = new Orc("Thrall", 50, nullptr, nullptr, 5, "Stun", img);

			Assert::AreEqual(Kimimaro.LauchSpecialCapacity(Billy, Thrall),S_OK);

            delete Thrall;
            Thrall = nullptr;
            delete MasterSword;
            MasterSword = nullptr;
            delete Billy;
            Billy = nullptr;



		}

		TEST_METHOD(LauchSpecialCapacityReturnS_FALSE)
		{
            Image img;
			GameGod Kimimaro;

			Sword* MasterSword = new Sword(10);
			Knigth* Billy = new Knigth("Billy", 60, MasterSword, nullptr, 3, "Charge", img);
			Orc* Thrall = new Orc("Thrall", 60, nullptr, nullptr, 5, "Stun", img);

			Assert::AreEqual(Kimimaro.LauchSpecialCapacity(Billy, Thrall), S_FALSE);
            delete MasterSword;
            MasterSword = nullptr;
            delete Billy;
            Billy = nullptr;
            delete Thrall;
            Thrall = nullptr;
		}

		TEST_METHOD(LauchSpecialCapacityReturnE_Fail)
		{
            Image img;
			GameGod Kimimaro;

			Knigth* Billy = new Knigth("Billy", 20, nullptr, nullptr, 3, "Charge", img);
			Orc* Thrall = new Orc("Thrall", 60, nullptr, nullptr, 5, "Stun", img);

			Assert::AreEqual( Kimimaro.LauchSpecialCapacity(nullptr, Thrall),E_FAIL);
			Assert::AreEqual(Kimimaro.LauchSpecialCapacity(Billy, nullptr), E_FAIL);
			Assert::AreEqual(Kimimaro.LauchSpecialCapacity(nullptr, nullptr), E_FAIL);
            delete Billy;
            Billy = nullptr;
            delete Thrall;
            Thrall = nullptr;
		}

		TEST_METHOD(isAWinnerDecidedIsTrue)
		{
            Image img;
			GameGod Kimimaro;

			Knigth* Billy = new Knigth("Billy", 0, nullptr, nullptr, 3, "Charge", img);
			Orc* Thrall = new Orc("Thrall", 60, nullptr, nullptr, 5, "Stun", img);

			Assert::AreEqual(Kimimaro.isAWinnerDecided(Billy, Thrall),S_OK);
            delete Billy;
            Billy = nullptr;
            delete Thrall;
            Thrall = nullptr;
		}
		
		TEST_METHOD(isAWinnerDecidedIsFalse)
		{
            Image img;
			GameGod Kimimaro;

			Knigth* Billy = new Knigth("Billy", 20, nullptr, nullptr, 3, "Charge", img);
			Orc* Thrall = new Orc("Thrall", 60, nullptr, nullptr, 5, "Stun", img);

			Assert::AreEqual(Kimimaro.isAWinnerDecided(Billy, Thrall),S_FALSE);
            delete Billy;
            Billy = nullptr;
            delete Thrall;
            Thrall = nullptr;
		}

		TEST_METHOD(ClassicFightIsTrue)
		{
            Image img;
			GameGod Kimimaro;

			Knigth* Billy = new Knigth("Billy", 1, nullptr, nullptr, 3, "Charge", img);
			Orc* Thrall = new Orc("Thrall", 60, nullptr, nullptr, 5, "Stun", img);

			Assert::AreEqual(Kimimaro.ClassicFight(Billy, Thrall),S_OK);
            delete Billy;
            Billy = nullptr;
            delete Thrall;
            Thrall = nullptr;
		}

		TEST_METHOD(ClassicFightIsFalse)
		{
            Image img;
			GameGod Kimimaro;

			Knigth* Billy = new Knigth("Billy", 20, nullptr, nullptr, 3, "Charge", img);
			Orc* Thrall = new Orc("Thrall", 60, nullptr, nullptr, 5, "Stun", img);

			Assert::AreEqual(Kimimaro.ClassicFight(Billy, Thrall), S_FALSE);
            delete Billy;
            Billy = nullptr;
            delete Thrall;
            Thrall = nullptr;
		}

		TEST_METHOD(CheckStatusEffectCureStun)
		{
            Image img;
			GameGod Kimimaro;

			Knigth* Billy = new Knigth("Billy", 20, nullptr, nullptr, 3, "Charge", img);

			Billy->setCharacterStatus(STUN);
			Kimimaro.CheckStatusEffect(Billy);

			Assert::AreEqual((int)Billy->getCharacterStatus(), (int)NORMAL);
            delete Billy;
            Billy = nullptr;
		}
		TEST_METHOD(CheckStatusEffectForPlayersCureStunForBilly)
		{
            Image img;
			GameGod Kimimaro;

			Knigth* Billy = new Knigth("Billy", 20, nullptr, nullptr, 3, "Charge", img);
			Orc* Thrall = new Orc("Thrall", 60, nullptr, nullptr, 5, "Stun", img);

			Billy->setCharacterStatus(STUN);
			Thrall->setCharacterStatus(BURN);
			Kimimaro.CheckStatusEffectForPlayers(Billy, Thrall);

			Assert::AreEqual((int)Billy->getCharacterStatus(), (int)NORMAL);
			Assert::AreEqual((int)Thrall->getCharacterStatus(), (int)BURN);
            delete Billy;
            Billy = nullptr;
            delete Thrall;
            Thrall = nullptr;
		}

		TEST_METHOD(GetWinnerReturnBilly)
		{
            Image img;
			GameGod Kimimaro;

			Knigth* Billy = new Knigth("Billy", 20, nullptr, nullptr, 3, "Charge", img);
			Kimimaro.setWinner(Billy);
			Assert::AreEqual(Kimimaro.GetWinner()->GetName(), Billy->GetName());
            delete Billy;
            Billy = nullptr;
		}
	};
}
