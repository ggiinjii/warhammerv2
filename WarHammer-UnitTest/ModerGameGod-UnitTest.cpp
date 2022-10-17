#include "pch.h"
#include "CppUnitTest.h"
#include "Inventory/Armor/SubArmor/Shield.h"
#include "Tool/Image.h"
#include "Character/Alliance/Knigth.h"
#include "Character/Horde/Orc.h"
#include "Tool/Pv.h"
#include "GameObject/ModernGameGod.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ModernGameGodUnitTest
{
	TEST_CLASS(ModernGameGod_UnitTest)
	{
	public:

		TEST_METHOD(StartModernBattleReturnS_OK)
		{			
            Image img;
			ModernGameGod Kimimaro;

			Knigth* Billy = new Knigth("Billy", 1, nullptr, nullptr, 3, "Charge", img);
			Orc* Thrall = new Orc("Thrall", 200, nullptr, nullptr, 5, "Stun", img);
			
			TurnInformation resultFight=Kimimaro.StartModernBattle( Billy, Thrall);
			
			Assert::AreEqual(0,resultFight.getPvAllianceFighter().getPv() );
			Assert::AreEqual(S_OK,resultFight.getIsExecutionWell() );
			Assert::AreEqual("Thrall",resultFight.getWinner().c_str() );
			Assert::AreEqual(1,resultFight.getTurnNumber() );
            Assert::IsTrue(resultFight.getIsGameOver());
			
		}
		
		
		
		TEST_METHOD(StartModernBattleReturnE_FAIL)
		{			
            Image img;
			ModernGameGod Kimimaro;

			Orc* Thrall = new Orc("Thrall", 200, nullptr, nullptr, 5, "Stun", img);
			
			TurnInformation resultFight=Kimimaro.StartModernBattle( nullptr, Thrall);
			
			Assert::AreEqual(E_FAIL,resultFight.getIsExecutionWell() );
            delete Thrall;
            Thrall = nullptr;
			
		}
		
				TEST_METHOD(NextTurnReturnS_OK)
		{			
            Image img;
			ModernGameGod Kimimaro;

			Knigth* Billy = new Knigth("Billy", 1, nullptr, nullptr, 3, "Charge", img);
			Orc* Thrall = new Orc("Thrall", 200, nullptr, nullptr, 5, "Stun", img);
			
			TurnInformation resultFight=Kimimaro.NextTurn( Billy, Thrall);
			
			Assert::AreEqual(0,resultFight.getPvAllianceFighter().getPv());
			Assert::AreEqual(S_OK,resultFight.getIsExecutionWell() );
			Assert::AreEqual("Thrall",resultFight.getWinner().c_str());
			Assert::AreEqual(1,resultFight.getTurnNumber() );
			Assert::IsTrue(resultFight.getIsGameOver() );
			
		}
		
		TEST_METHOD(NextTurnReturnE_FAIL)
		{			
            Image img;
			ModernGameGod Kimimaro;

			Orc* Thrall = new Orc("Thrall", 200, nullptr, nullptr, 5, "Stun", img);
			
			TurnInformation resultFight=Kimimaro.NextTurn( nullptr, Thrall);
			
	
			Assert::AreEqual(E_FAIL,resultFight.getIsExecutionWell() );

            delete Thrall;
            Thrall = nullptr;
		}
    
	
			TEST_METHOD(LauchSpecialCapacityReturnE_FAIL)
		{			
            Image img;
			ModernGameGod Kimimaro;

			Orc* Thrall = new Orc("Thrall", 200, nullptr, nullptr, 5, "Stun", img);
			
			HRESULT resultFight=Kimimaro.LauchSpecialCapacity( nullptr, Thrall);
			
			Assert::AreEqual(E_FAIL,resultFight );

            delete Thrall;
            Thrall = nullptr;
		}
		
		TEST_METHOD(LauchSpecialCapacityReturnS_OK)
		{			
            Image img;
			ModernGameGod Kimimaro;

			Knigth* Billy = new Knigth("Billy", 400, nullptr, nullptr, 3, "Charge", img);
			Orc* Thrall = new Orc("Thrall", 1, nullptr, nullptr, 5, "Stun", img);
			
			HRESULT resultFight=Kimimaro.LauchSpecialCapacity( Billy, Thrall);
			
			Assert::AreEqual(S_OK,resultFight );
			
		}
		
		TEST_METHOD(LauchSpecialCapacityReturnS_False)
		{			
            Image img;
			ModernGameGod Kimimaro;

			Knigth* Billy = new Knigth("Billy", 200, nullptr, nullptr, 3, "Charge", img);
			Orc* Thrall = new Orc("Thrall", 200, nullptr, nullptr, 5, "Stun", img);
			
			HRESULT resultFight=Kimimaro.LauchSpecialCapacity( Billy, Thrall);
			
			Assert::AreEqual(S_FALSE,resultFight );

            delete Billy;
            Billy = nullptr;
            delete Thrall;
            Thrall = nullptr;
		}
	
	
			TEST_METHOD(isAWinnerDecidedReturnS_False)
		{			
            Image img;
			ModernGameGod Kimimaro;

			Knigth* Billy = new Knigth("Billy", 200, nullptr, nullptr, 3, "Charge", img);
			Orc* Thrall = new Orc("Thrall", 200, nullptr, nullptr, 5, "Stun", img);
			
			HRESULT resultFight=Kimimaro.isAWinnerDecided( Billy, Thrall);
			
			Assert::AreEqual(S_FALSE,resultFight );
            delete Billy;
            Billy = nullptr;
            delete Thrall;
            Thrall = nullptr;
			
		}
		
			TEST_METHOD(isAWinnerDecidedReturnS_OK)
		{			
            Image img;
			ModernGameGod Kimimaro;

			Knigth* Billy = new Knigth("Billy", 200, nullptr, nullptr, 3, "Charge", img);
			Orc* Thrall = new Orc("Thrall", 0, nullptr, nullptr, 5, "Stun", img);
			
			HRESULT resultFight=Kimimaro.isAWinnerDecided( Billy, Thrall);
			
			Assert::AreEqual(S_OK,resultFight );
		}
	
		TEST_METHOD(isAWinnerDecidedReturnE_Fail)
		{			
            Image img;
			ModernGameGod Kimimaro;

			Orc* Thrall = new Orc("Thrall", 200, nullptr, nullptr, 5, "Stun", img);
			
			HRESULT resultFight=Kimimaro.ClassicFight( nullptr, Thrall);
			
			Assert::AreEqual(E_FAIL,resultFight );

            delete Thrall;
            Thrall = nullptr;
		}
	
				TEST_METHOD(ClassicFightReturnS_OK)
		{			
            Image img;
			ModernGameGod Kimimaro;

			Knigth* Billy = new Knigth("Billy", 200, nullptr, nullptr, 3, "Charge", img);
			Orc* Thrall = new Orc("Thrall", 1, nullptr, nullptr, 5, "Stun", img);
			
			HRESULT resultFight=Kimimaro.ClassicFight( Billy, Thrall);
			
			Assert::AreEqual(S_OK,resultFight );
		}
		
				TEST_METHOD(ClassicFightReturnS_False)
		{			
            Image img;
			ModernGameGod Kimimaro;

			Knigth* Billy = new Knigth("Billy", 200, nullptr, nullptr, 3, "Charge", img);
			Orc* Thrall = new Orc("Thrall", 100, nullptr, nullptr, 5, "Stun", img);
			
			HRESULT resultFight=Kimimaro.ClassicFight( Billy, Thrall);
			
			Assert::AreEqual(S_FALSE,resultFight );

            delete Thrall;
            Thrall = nullptr;
            delete Billy;
            Billy = nullptr;
		}
            
		TEST_METHOD(CheckStatusEffectForPlayersSetStatusToNormalIfStun)
		{			
            Image img;
			ModernGameGod Kimimaro;

			Knigth* Billy = new Knigth("Billy", 200, nullptr, nullptr, 3, "Charge", img);
			Orc* Thrall = new Orc("Thrall", 100, nullptr, nullptr, 5, "Stun", img);
			
			Thrall->setCharacterStatus(STUN);
			
			Kimimaro.CheckStatusEffectForPlayers( Billy, Thrall);
			
			Assert::AreEqual((int)NORMAL, (int)Thrall->getCharacterStatus() );
			Assert::AreEqual((int)NORMAL, (int)Billy->getCharacterStatus());

            delete Billy;
            Billy = nullptr;
            delete Thrall;
            Thrall = nullptr;
		}
	
		TEST_METHOD(CheckStatusEffectForPlayersNoChangeOfStatus)
		{			
            Image img;
			ModernGameGod Kimimaro;

			Knigth* Billy = new Knigth("Billy", 200, nullptr, nullptr, 3, "Charge", img);
			Orc* Thrall = new Orc("Thrall", 100, nullptr, nullptr, 5, "Stun", img);
			
            Billy->setCharacterStatus(STUN);
			Thrall->setCharacterStatus(BURN);
			
			Kimimaro.CheckStatusEffect(Thrall);
			Kimimaro.CheckStatusEffect(Billy);
			
			Assert::AreEqual((int)BURN, (int)Thrall->getCharacterStatus() );
			Assert::AreEqual((int)NORMAL, (int)Billy->getCharacterStatus());

            delete Billy;
            Billy = nullptr;
            delete Thrall;
            Thrall = nullptr;
		}
        
			
	};
}
