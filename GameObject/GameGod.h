#pragma once
#include "Character/Character.h"
#include "plog/Log.h"
#include "Ui/RetroUi.h"
#include <string>
#include <list>

#include <fstream>
#include "Ui/ModernUi.h"
#include "include/nlohmann/json.hpp"

using json = nlohmann::json;

class GameGod
{
private: 
	Character* _winner;

    /*Opponent for retroUI*/
	Character* _goodGuy;
	Character* _badGuy;

    /*List of fighter loaded by Json*/
	std::vector<Character*> GoodGuy;
	std::vector<Character*> BadGuy;

    // Retro UI
	RetroUi _retroUI;

    //Modern UI
    ModernUi _ModernUI;
	
    //Game Mandatory Variable
    HRESULT _isGameOver ;
    int _turnCount;

public: 
	GameGod(void);
	~GameGod();

	HRESULT LoadCharacterRessources(string fileName);


	HRESULT LauchSpecialCapacity(Character *a, Character *b);
	HRESULT ClassicFight(Character *a, Character *b);

	Character* GetWinner();

	void setWinner(Character* winner);

	HRESULT isAWinnerDecided(Character* character1, Character* character2);

	void SetOpponent(Character* character1, Character* character2);
	void CheckStatusEffectForPlayers(Character* a, Character* b);
	void CheckStatusEffect(Character* character1);

	void StartRetroBattle(Character* goodGuy, Character* badGuy);
    void StartModernBattle(Character* goodGuy, Character* badGuy);
    bool NextTurn(Character* goodGuy, Character* badGuy);
	
	void AddTurnInfo(string info);
	void resetTurnInfo();

	void RetroPlay(Character* goodGuy, Character* badGuy);
	void ModernPlay();

    std::vector<Character*> GetGoodGuy() { return GoodGuy; };
    std::vector<Character*> GetBadGuy() { return BadGuy; };
};

