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
	Character* _allianceFighter;
	Character* _hordeFighter;

    /*List of fighter loaded by Json*/
	std::vector<Character*> _allianceFighters;
	std::vector<Character*> _hordeFighters;

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


	HRESULT LauchSpecialCapacity(Character *allianceFighter, Character *hordeFighter);
	HRESULT ClassicFight(Character *allianceFighter, Character *hordeFighter);

	Character* GetWinner();

	void setWinner(Character* winner);

	HRESULT isAWinnerDecided(Character* allianceFighter, Character* hordeFighter);

	void SetOpponent(Character* allianceFighter, Character* hordeFighter);
	void CheckStatusEffectForPlayers(Character* allianceFighter, Character* hordeFighter);
	void CheckStatusEffect(Character* allianceFighter);

	void StartRetroBattle(Character* allianceFighter, Character* hordeFighter);
    void StartModernBattle(Character* allianceFighter, Character* hordeFighter);
    HRESULT NextTurn(Character* allianceFighter, Character* hordeFighter);
	
	void AddTurnInfo(string info);
	void resetTurnInfo();

	void RetroPlay();

    std::vector<Character*> GetGoodGuy() { return _allianceFighters; };
    std::vector<Character*> GetBadGuy() { return _hordeFighters; };

    void DisplayNameFighter(vector<Character*> Fighter);
    void DisplayFighter(Character*  Fighter);

    int SecureCinInput(int maxNumber);
};

