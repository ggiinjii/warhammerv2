#include "GameObject/GameGod.h"
#include "Character/Alliance/Knigth.h"
#include "Character/Horde/Orc.h"
#include "Character/Character.h"
#include "Inventory/Weapon/SubWeapon/Hammer.h"
#include "Inventory/Armor/SubArmor/MirrorArmor.h"
#include "Ui/ModernUi.h"
#include <iostream>
#include "Tool//Image.h"

GameGod::GameGod(void)
{
	_winner = nullptr;
	_goodGuy= nullptr;
	_badGuy= nullptr;
    _isGameOver = E_FAIL;
    _turnCount = 0;
}

GameGod::~GameGod()
{
}

HRESULT GameGod::LoadCharacterRessources( string fileName)
{
	json data = nullptr;

	try {
		///Parser JSON 
		std::ifstream f(fileName);
		data=json::parse(f);
	}
	catch (exception e)
	{
		PLOG_ERROR << "Parsing of Json Failed. Filename: "<< fileName;
		throw e;
	}

	auto Characters = data["Character"];
	int nbCharacter = Characters.size();


	/*********************************************CHARACTER CREATION***********************************************/

	for (int i = 0; i < nbCharacter; i++)
	{

		string name = Characters[i]["Name"];
		int pv = Characters[i]["pv"];
		
		Weapon* CharacterWeapon = new Weapon();;
		Armor* CharacterArmor = new Armor();;

        /*********************************************SWORD CREATION***********************************************/
        if (!Characters[i]["MyWeapon"].empty())
        {
            string weapon = Characters[i]["MyWeapon"]["type"];

            if (weapon == "Sword")
            {
                CharacterWeapon = new Sword();
            }
            else if (weapon == "Hammer")
            {
                CharacterWeapon = new Hammer();
            }
            CharacterWeapon->setDamage(Characters[i]["MyWeapon"]["damage"]);

            string weaponName= Characters[i]["MyWeapon"]["Name"];
            CharacterWeapon->SetName(weaponName);
        }
        else
        {
            CharacterWeapon->setDamage(0);
            CharacterWeapon->SetName("None");
        }
		/*********************************************ARMOR CREATION***********************************************/
 

        if (!Characters[i]["MyArmor"].empty())
        {
            string armor = Characters[i]["MyArmor"]["type"];

            if (armor == "Shield")
            {
                CharacterArmor = new Shield();
            }
            else if (armor == "MirrorArmor")
            {
                CharacterArmor = new MirrorArmor();
            }
            CharacterArmor->setPvBonus(Characters[i]["MyArmor"]["pvBonus"]);
            string armorName = Characters[i]["MyArmor"]["Name"];
            CharacterArmor->SetName(armorName);
        }
        else
        {
            CharacterArmor->setPvBonus(0);
            CharacterArmor->SetName("None");
        }


		int cdCapacity = Characters[i]["CdCapacity"];
			string nameCapacity = Characters[i]["NameCapacity"];

		Character* newCharacter = nullptr;

		string characterClass = Characters[i]["Class"];

        Image associateImg(Characters[i]["ImgSource"], Characters[i]["SizeImg"]["Height"], Characters[i]["SizeImg"]["Width"]);

		/*********************************************CLASS CREATION***********************************************/

		if (characterClass == "Orc")
		{
			newCharacter = new Orc(name, pv, CharacterWeapon, CharacterArmor,cdCapacity ,nameCapacity, associateImg);
			
		}
		else if (characterClass == "Knight")
		{
			newCharacter = new Knigth(name, pv, CharacterWeapon, CharacterArmor, cdCapacity, nameCapacity, associateImg);
			
		}

		int ForceSide = Characters[i]["Alignement"];

		switch (ForceSide)
		{
		case 0: 
            BadGuy.push_back((Knigth*)newCharacter); // Light Side
			break;

		case 1: 
            GoodGuy.push_back((Orc*)newCharacter); // Dark Side
			break;

		default: 
			GoodGuy.push_back((Knigth*)newCharacter); // Let's assume that we are all good is 
			break;
		}
	}
	return S_OK;
}

HRESULT GameGod::LauchSpecialCapacity(Character *a, Character *b)
{
	if (a == nullptr || b == nullptr)
	{
		AddTurnInfo("Error with Character. Check logfile\n");
		PLOG_ERROR << "One of the caracter is Null:" <<" - Character A: "<<a<<" - Character B:"<<b;
		return E_FAIL;
	}

	AddTurnInfo(a->GetName() + " Launch Special Capacity");

	HRESULT result=a->SpecialCapacityCheck(b);

	std::list<string> characterlog = a->GetLog();

	for (auto const& i : characterlog) {
		AddTurnInfo(i);
	}


	HRESULT isAPlayerDead = isAWinnerDecided(a, b);

	if (isAPlayerDead==S_FALSE)
	{
		AddTurnInfo( b->GetName() + " Launch Special Capacity");

		b->SpecialCapacityCheck(a);
		
		characterlog = b->GetLog();

		for (auto const& i : characterlog) {
			AddTurnInfo(i);
		}

		isAPlayerDead = isAWinnerDecided(a, b);
	}

	a->ClearLog();
	b->ClearLog();

	return isAPlayerDead;
	
}


HRESULT GameGod::isAWinnerDecided(Character* character1, Character* character2)
{
	if (!character1->IsCharacterStillAlive())
	{
		setWinner(character2);
		return S_OK;
	}
	else if (!character2->IsCharacterStillAlive())
	{
		setWinner(character1);
		return S_OK;
	}
	else
		return S_FALSE;
}

HRESULT GameGod::ClassicFight(Character *a, Character *b)
{
	AddTurnInfo("Character " + a->GetName() + " Attack normaly");

	a->Attack(b);

	std::list<string> characterlog = a->GetLog();

	for (auto const& i : characterlog) {
		AddTurnInfo(i);
	}


	if (isAWinnerDecided(a, b)==S_FALSE)
	{
		AddTurnInfo("\nCharacter " + b->GetName() + " Attack normaly");

		b->Attack(a);

		characterlog = b->GetLog();

		for (auto const& i : characterlog) {
			AddTurnInfo(i);
		}
	}

	a->ClearLog();
	b->ClearLog();

	return isAWinnerDecided(a, b);
}

void GameGod::CheckStatusEffectForPlayers(Character* a, Character* b)
{
	CheckStatusEffect( a);
	CheckStatusEffect( b);

}


void GameGod::CheckStatusEffect(Character *a )
{
	CONDITION status= a->getCharacterStatus();
	switch (status)
	{
		case STUN: a->setCharacterStatus(NORMAL);
			AddTurnInfo("Character " + a->GetName() + " Cured from STUN");
			break;

		case BURN: //TODO
		
		case FROZEN: //TODO

		case NORMAL: 
			AddTurnInfo(a->GetName() + " status is NORMAL");

		default: 

			break;
	}
	

}

void GameGod::StartRetroBattle(Character* goodGuy, Character *badGuy)
{
     _isGameOver = E_FAIL;
     _turnCount = 0;

	_retroUI.SetOpponent(goodGuy->GetName(), badGuy->GetName());

	PLOG_INFO << "The battle Begin";
	while (_isGameOver != S_OK)
	{
        _isGameOver = NextTurn(goodGuy, badGuy);
	}
}

void GameGod::StartModernBattle(Character* goodGuy, Character* badGuy)
{
    _isGameOver = E_FAIL;
    _turnCount = 0;

    PLOG_INFO << "The battle Begin";

    _isGameOver = NextTurn(goodGuy, badGuy);

}

bool GameGod::NextTurn(Character* goodGuy, Character* badGuy)
{

    resetTurnInfo();

    _turnCount = _turnCount + 1;
    PLOG_INFO << "Turn No" << _turnCount;
    _retroUI.SetTurnNumber(_turnCount);

    AddTurnInfo("\nSpecial Capacity Phase");
    _isGameOver = LauchSpecialCapacity(goodGuy, badGuy);

    if (_isGameOver != S_OK)
    {
        AddTurnInfo("\nClassic Combat Phase");
        _isGameOver = ClassicFight(goodGuy, badGuy);

        if (_isGameOver == S_FALSE)
        {
            AddTurnInfo("Check Condition of both players");
            CheckStatusEffectForPlayers(goodGuy, badGuy);
        }
        else {
            _isGameOver = S_OK;
        }
    }

    AddTurnInfo("End Of Turn\n");
    _retroUI.SetPvOpponent(goodGuy->GetPv(), badGuy->GetPv());
    _retroUI.displayUI();

    system("pause");
    return _isGameOver;
}


void GameGod::AddTurnInfo(string info)
{
	PLOG_INFO << info;
	_retroUI.AddTurnInfo(info);
}

void GameGod::resetTurnInfo()
{
	_retroUI.ResetTurnInfo();
}

void GameGod::RetroPlay(Character * goodGuy, Character* badGuy)
{
	/******************CHOIX DE L'ADVERSAIRE************************/

	cout << "Welcome to the Arena of Azeroth. Let's the fight between Aliance and horde Begin\n";

	StartRetroBattle(goodGuy, badGuy);

	resetTurnInfo();
	AddTurnInfo("The Game is Over.");
	AddTurnInfo("The Winner is " + GetWinner()->GetName() );

	_retroUI.displayUI();
}



void GameGod::SetOpponent(Character* character1, Character* character2)
{
	_goodGuy = character1;
	_badGuy = character2;
}

void GameGod::setWinner(Character* winner)
{
	PLOG_INFO << "We have a winner ";

	_winner = winner;
}

Character* GameGod::GetWinner()
{
	return _winner;
}
